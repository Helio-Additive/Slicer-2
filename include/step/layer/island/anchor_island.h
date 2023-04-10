#ifndef ANCHOR_ISLAND_H
#define ANCHOR_ISLAND_H

// Local
#include "step/layer/island/island_base.h"

namespace ORNL {
    /*!
     * \class RaftIsland
     * \brief Island type for rafts.
     */
    class AnchorIsland : public IslandBase {
        public:
            //! \brief Constructor
            //! \param geometry: the outlines
            //! \param sb: the settings
            //! \param settings_polygons: a vector of settings polygons to apply
            AnchorIsland(const PolygonList& geometry, const QSharedPointer<SettingsBase>& sb, const QVector<SettingsPolygon>& settings_polygons);

            //! \brief Override from base. Filters down to individual regions to add
            //! travels and apply path modifiers
            void optimize(QSharedPointer<PathOrderOptimizer> poo, Point& currentLocation, QVector<QSharedPointer<RegionBase>>& previousRegions) override;
    };
}  // namespace ORNL
#endif  // ANCHOR_ISLAND_H
