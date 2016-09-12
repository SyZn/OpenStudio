/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include <gtest/gtest.h>

#include "ModelFixture.hpp"

#include "../BuildingUnit.hpp"
#include "../BuildingUnit_Impl.hpp"
#include "../RenderingColor.hpp"
#include "../RenderingColor_Impl.hpp"

#include "../../utilities/units/Quantity.hpp"
#include "../../utilities/units/Unit.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, BuildingUnit_RenderingColor)
{

    Model model;
    // TODO: Check constructor.
    BuildingUnit buildingUnit(model);
    RenderingColor color1(model);

    color1.setRenderingRedValue(255);
    color1.setRenderingGreenValue(0);
    color1.setRenderingBlueValue(0);
    color1.setRenderingAlphaValue(255);

    EXPECT_FALSE(buildingUnit.renderingColor());

    ASSERT_TRUE(buildingUnit.setRenderingColor(color1));

    boost::optional<RenderingColor> color2 = buildingUnit.renderingColor();
    ASSERT_TRUE(color2);

    EXPECT_EQ(color2->renderingRedValue(), 255);
    EXPECT_EQ(color2->renderingGreenValue(), 0);
    EXPECT_EQ(color2->renderingBlueValue(), 0);
    EXPECT_EQ(color2->renderingAlphaValue(), 255);

    buildingUnit.resetRenderingColor();
    ASSERT_FALSE(buildingUnit.renderingColor());

}


