/*
 * Copyright © 2018  Google, Inc.
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 */

#include "hb-test.h"

#include <hb.h>
#include <hb-ot.h>
#include <hb-aat.h>

/* Unit tests for hb-aat.h */

static hb_face_t *face;
static hb_face_t *sbix;

static void
test_aat_get_features (void)
{
  hb_aat_layout_feature_type_t features[3];
  unsigned int count = 3;
  g_assert_cmpuint (11, ==, hb_aat_layout_get_features (face, 0, &count, features));

  g_assert_cmpuint (1, ==, features[0]);
  g_assert_cmpuint (3, ==, features[1]);
  g_assert_cmpuint (6, ==, features[2]);

  g_assert_cmpuint (258, ==, hb_aat_layout_feature_get_name_id (face, features[0]));
  g_assert_cmpuint (261, ==, hb_aat_layout_feature_get_name_id (face, features[1]));
  g_assert_cmpuint (265, ==, hb_aat_layout_feature_get_name_id (face, features[2]));
}

static void
test_aat_get_feature_selectors (void)
{
  hb_aat_layout_feature_selector_t default_selector;
  hb_aat_layout_feature_selector_t settings[3];
  unsigned int count = 3;

  g_assert_cmpuint (4, ==, hb_aat_layout_feature_get_selectors (face, HB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE,
							        &default_selector, 0, &count, settings));
  g_assert_cmpuint (3, ==, count);
  g_assert_cmpuint (0, ==, default_selector);

  g_assert_cmpuint (0, ==, settings[0]);
  g_assert_cmpuint (294, ==, hb_aat_layout_feature_selector_get_name_id (face, HB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE, settings[0]));

  g_assert_cmpuint (1, ==, settings[1]);
  g_assert_cmpuint (295, ==, hb_aat_layout_feature_selector_get_name_id (face, HB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE, settings[1]));

  g_assert_cmpuint (2, ==, settings[2]);
  g_assert_cmpuint (296, ==, hb_aat_layout_feature_selector_get_name_id (face, HB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE, settings[2]));

  g_assert_cmpuint (HB_OT_NAME_ID_INVALID, ==, hb_aat_layout_feature_selector_get_name_id (face, HB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE, HB_AAT_LAYOUT_SELECTOR_INVALID));

  count = 3;
  g_assert_cmpuint (4, ==, hb_aat_layout_feature_get_selectors (face, HB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE,
								&default_selector, 3, &count, settings));
  g_assert_cmpuint (1, ==, count);
  g_assert_cmpuint (0, ==, default_selector);

  g_assert_cmpuint (3, ==, settings[0]);
  g_assert_cmpuint (297, ==, hb_aat_layout_feature_selector_get_name_id (face, HB_AAT_LAYOUT_FEATURE_TYPE_DESIGN_COMPLEXITY_TYPE, settings[0]));

  count = 1;
  g_assert_cmpuint (1, ==, hb_aat_layout_feature_get_selectors (face, HB_AAT_LAYOUT_FEATURE_TYPE_TYPOGRAPHIC_EXTRAS,
								&default_selector, 0, &count, settings));
  g_assert_cmpuint (1, ==, count);
  g_assert_cmpuint (HB_AAT_LAYOUT_FEATURE_TYPE_INVALID, ==, default_selector);

  g_assert_cmpuint (8, ==, settings[0]);
  g_assert_cmpuint (308, ==, hb_aat_layout_feature_selector_get_name_id (face, HB_AAT_LAYOUT_FEATURE_TYPE_TYPOGRAPHIC_EXTRAS, settings[0]));

  count = 100;
  g_assert_cmpuint (0, ==, hb_aat_layout_feature_get_selectors (face, HB_AAT_LAYOUT_FEATURE_TYPE_INVALID,
								NULL, 0, &count, settings));
  g_assert_cmpuint (0, ==, count);

  g_assert_cmpuint (HB_OT_NAME_ID_INVALID, ==, hb_aat_layout_feature_selector_get_name_id (sbix, HB_AAT_LAYOUT_FEATURE_TYPE_INVALID,
											   (hb_aat_layout_feature_selector_t) 0));
}

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_aat_get_features);
  hb_test_add (test_aat_get_feature_selectors);

  face = hb_test_open_font_file ("fonts/aat-feat.ttf");
  sbix = hb_test_open_font_file ("fonts/chromacheck-sbix.ttf");
  unsigned int status = hb_test_run ();
  hb_face_destroy (sbix);
  hb_face_destroy (face);
  return status;
}
