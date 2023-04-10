#ifndef PERIMETER_SECTOR_H
#define PERIMETER_SECTOR_H

// Local
#include "step/layer/regions/region_base.h"
#include "geometry/segments/line.h"

namespace ORNL {
    class PerimeterSector : public RegionBase {
        public:
            //! \brief Constructor
            //! \param sb: the settings
            //! \param index: index based on region ordering
            //! \param settings_polygons: a vector of settings polygons to apply
            PerimeterSector(const QSharedPointer<SettingsBase>& sb, const int index, const QVector<SettingsPolygon>& settings_polygons);

            //! \brief Writes the gcode for the perimeter.
            //! \param writer Writer type to use for gcode output
            QString writeGCode(QSharedPointer<WriterBase> writer) override;

            //! \brief Computes the perimeter region.
            void compute(uint layer_num, QSharedPointer<SyncManager>& sync) override;

            //! \brief Optimizes the region.
            //! \param poo: currently loaded path optimizer
            //! \param innerMostClosedContour: used for subsequent path modifiers
            //! \param outerMostClosedContour: used for subsequent path modifiers
            //! \param current_location: most recent location
            //! \param shouldNextPathBeCCW: state as to CW or CCW of previous path for use with additional DOF
            void optimize(QSharedPointer<PathOrderOptimizer> poo, Point& current_location,
                          QVector<Path>& innerMostClosedContour, QVector<Path>& outerMostClosedContour,
                          bool& shouldNextPathBeCCW) override;

            //! \brief Creates paths for the perimeter region.
            void createPaths();

            //! \brief Set geometry as computed in RPBF slicer
            //! \param perimeters: polyline representation of perimeters in sector
            void setComputedGeometry(QVector<Polyline> perimeters);

            //! \brief Set starting vector
            //! \param p: point that represents "starting" vector for circular ordering
            void setStartVector(Point p);
        private:

            //! \brief Creates modifiers
            //! \param path: Current path to add modifiers to
            //! \param supportsG3: Whether or not G2/G3 is supported for spiral lift
            //! \param innerMostClosedContour: used for Prestarts (currently only skins/infill)
            //! \param current_location: used to update start points of travels after modifiers are added
            void calculateModifiers(Path& path, bool supportsG3, QVector<Path>& innerMostClosedContour, Point& current_location) override;

            //! \brief Holds the computed geometry (perimeters) before it is converted into paths
            QVector<Polyline> m_computed_geometry;

            //! \brief Hold starting vector for sector
            Point m_start_vec;
    };
}

#endif // PERIMETER_SECTOR_H
