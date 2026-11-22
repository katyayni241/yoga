/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, wrap_reverse_accounts_for_trailing_cross_axis_padding) {
  YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetFlexWrap(root, YGWrapWrapReverse);
  YGNodeStyleSetWidth(root, 100.0f);
  YGNodeStyleSetHeight(root, 100.0f);
  YGNodeStyleSetPadding(root, YGEdgeBottom, 10.0f);

  YGNodeRef child = YGNodeNew();
  YGNodeStyleSetWidth(child, 10.0f);
  YGNodeStyleSetHeight(child, 10.0f);
  YGNodeInsertChild(root, child, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(80.0f, YGNodeLayoutGetTop(child));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, wrap_reverse_accounts_for_asymmetric_horizontal_padding) {
  YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetFlexWrap(root, YGWrapWrapReverse);
  YGNodeStyleSetWidth(root, 100.0f);
  YGNodeStyleSetHeight(root, 100.0f);
  YGNodeStyleSetPadding(root, YGEdgeLeft, 5.0f);
  YGNodeStyleSetPadding(root, YGEdgeRight, 15.0f);

  YGNodeRef child = YGNodeNew();
  YGNodeStyleSetWidth(child, 10.0f);
  YGNodeStyleSetHeight(child, 10.0f);
  YGNodeInsertChild(root, child, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  // In LTR, wrap-reverse mirrors within the content box. The child's left
  // edge is 100 - 15px right padding - 10px child width.
  ASSERT_FLOAT_EQ(75.0f, YGNodeLayoutGetLeft(child));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, wrap_reverse_accounts_for_asymmetric_horizontal_border) {
  YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetFlexWrap(root, YGWrapWrapReverse);
  YGNodeStyleSetWidth(root, 100.0f);
  YGNodeStyleSetHeight(root, 100.0f);
  YGNodeStyleSetBorder(root, YGEdgeLeft, 5.0f);
  YGNodeStyleSetBorder(root, YGEdgeRight, 15.0f);

  YGNodeRef child = YGNodeNew();
  YGNodeStyleSetWidth(child, 10.0f);
  YGNodeStyleSetHeight(child, 10.0f);
  YGNodeInsertChild(root, child, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(75.0f, YGNodeLayoutGetLeft(child));

  YGNodeFreeRecursive(root);
}
