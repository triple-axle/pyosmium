#ifndef PYOSMIUM_OSM_WRAPPER_HPP
#define PYOSMIUM_OSM_WRAPPER_HPP

#include <osmium/osm.hpp>

class COSMObject {
    public:
        osmium::OSMObject const *get_object() const {
            auto const *obj = object_ptr();
            if (!obj) {
                throw std::runtime_error{"Access to removed object"};
            }
            return obj;
        }

    protected:
        virtual osmium::OSMObject const *object_ptr() const = 0;
};

template <typename T>
class COSMDerivedObject : public COSMObject {
    public:
        COSMDerivedObject(T *obj) : m_obj(obj) {}

        T const *get() const {
            if (!m_obj) {
                throw std::runtime_error{"Access to removed object"};
            }
            return m_obj;
        }

        void invalidate() { m_obj = nullptr; }

    protected:
        osmium::OSMObject const *object_ptr() const override { return m_obj; }

    private:
        T *m_obj;
};

using COSMNode = COSMDerivedObject<osmium::Node const>;
using COSMWay = COSMDerivedObject<osmium::Way const>;
using COSMRelation = COSMDerivedObject<osmium::Relation const>;
using COSMArea = COSMDerivedObject<osmium::Area const>;


class COSMChangeset {
    public:
        COSMChangeset(osmium::Changeset const *obj) : m_obj(obj) {}

        osmium::Changeset const *get() const {
            if (!m_obj) {
                throw std::runtime_error{"Access to removed object"};
            }
            return m_obj;
        }

        void invalidate() { m_obj = nullptr; }

    private:
        osmium::Changeset const *m_obj;
};


#endif //PYOSMIUM_OSM_WRAPPER_HPP

