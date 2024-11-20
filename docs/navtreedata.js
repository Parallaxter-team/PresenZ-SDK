/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "PresenZ SDK", "index.html", [
    [ "PresenZ plugin SDK - Programmer Manual", "index.html#autotoc_md58", [
      [ "Table of Contents", "index.html#autotoc_md59", null ]
    ] ],
    [ "General flow", "flow.html", [
      [ "1.1 Detection Phase", "flow.html#autotoc_md0", null ],
      [ "1.2 Render Phase", "flow.html#autotoc_md1", null ],
      [ "1.3 PresenZ Merger", "flow.html#autotoc_md2", null ]
    ] ],
    [ "Renderer requirements & recommendations", "requirements.html", [
      [ "2.1 Requirements", "requirements.html#autotoc_md3", [
        [ "2.1.1 Control the sub-sampling mechanism", "requirements.html#autotoc_md4", null ],
        [ "2.1.2 Ability to start a few renders in a row", "requirements.html#autotoc_md5", null ],
        [ "2.1.3 Ability to check if there’s a line of sight from point A to point B", "requirements.html#autotoc_md6", null ],
        [ "2.1.4 Ability to redefine ray origin/direction (and optionally derivatives)", "requirements.html#autotoc_md7", null ],
        [ "2.1.5 Extract hit location and normal for each sample hit", "requirements.html#autotoc_md8", null ],
        [ "2.1.6 Shade a target viewed location from a custom viewpoint", "requirements.html#autotoc_md9", null ]
      ] ],
      [ "2.2 Recommandations", "requirements.html#autotoc_md10", [
        [ "2.2.1 Processing patch of images in independent threads", "requirements.html#autotoc_md11", null ],
        [ "2.2.2 Ability to extract user properties from geometries", "requirements.html#autotoc_md12", null ],
        [ "2.2.3 Ability to shade twice in a row from different viewpoint", "requirements.html#autotoc_md13", null ],
        [ "2.2.4 Ability to extract velocity at specific location", "requirements.html#autotoc_md14", null ]
      ] ]
    ] ],
    [ "Initialization/Termination", "init_termination.html", [
      [ "3.1 Setting up PresenZ error reporting system", "init_termination.html#autotoc_md15", null ],
      [ "3.2 Phase initialization", "init_termination.html#autotoc_md16", null ],
      [ "3.3 Phase set up", "init_termination.html#autotoc_md17", [
        [ "3.3.1 Setting up AOVs", "init_termination.html#autotoc_md18", null ],
        [ "3.3.2 Setting up Rendering Resolution", "init_termination.html#autotoc_md19", [
          [ "3.3.2.1 First phase", "init_termination.html#autotoc_md20", null ],
          [ "3.3.2.2 Second phase", "init_termination.html#autotoc_md21", null ]
        ] ]
      ] ],
      [ "3.4 Phase Begin and Termination", "init_termination.html#autotoc_md22", null ]
    ] ],
    [ "Detection phase and render phase", "phases.html", [
      [ "4.1 Detection phase", "phases.html#autotoc_md23", [
        [ "4.1.1 Requirements", "phases.html#autotoc_md24", null ],
        [ "4.1.2 Casting Detection Rays", "phases.html#autotoc_md25", null ],
        [ "4.1.3 Creating a hit test callback function", "phases.html#autotoc_md26", [
          [ "4.1.3 Passing the hit test callback function to PresenZ", "phases.html#autotoc_md27", null ]
        ] ]
      ] ],
      [ "4.2 Render phase", "phases.html#autotoc_md28", [
        [ "4.2.1 Requirements", "phases.html#autotoc_md29", null ],
        [ "4.2.2 Casting Render Rays", "phases.html#autotoc_md30", null ],
        [ "4.2.3 Shading the Render Rays", "phases.html#autotoc_md31", null ],
        [ "4.2.4 Forwarding the shaded pixels to PresenZ", "phases.html#autotoc_md32", null ],
        [ "4.2.5 Forwarding AOVs to PresenZ", "phases.html#autotoc_md33", null ]
      ] ]
    ] ],
    [ "Buckets and Threading", "threading.html", [
      [ "5.1 What if there’s no bucket system in your renderer", "threading.html#autotoc_md34", null ],
      [ "5.2 Serializing buckets for distributed rendering", "threading.html#autotoc_md35", null ]
    ] ],
    [ "Transparency", "transparencies.html", [
      [ "6.1 Initialization", "transparencies.html#autotoc_md36", null ],
      [ "6.2 Easy detection of transparent geometry with tags", "transparencies.html#autotoc_md37", null ],
      [ "6.3 Referencing transparent geometry", "transparencies.html#autotoc_md38", null ]
    ] ],
    [ "Stereoscopic images", "stereo.html", [
      [ "7.1 if you can’t change the ray properties during shading", "stereo.html#autotoc_md39", null ]
    ] ],
    [ "Misc.: Hair and Animation", "hair.html", [
      [ "8.1 Hair", "hair.html#autotoc_md40", null ],
      [ "8.2 Animations", "hair.html#autotoc_md41", [
        [ "8.2.1 Frame numbering", "hair.html#autotoc_md42", null ],
        [ "8.2.2 Movement interpolation", "hair.html#autotoc_md43", null ]
      ] ]
    ] ],
    [ "Implementation in Vray", "vray.html", [
      [ "9.1 Camera", "vray.html#autotoc_md44", [
        [ "9.1.1 presenz_camera.h", "vray.html#autotoc_md45", null ],
        [ "9.1.2 presenz_camera.cpp", "vray.html#autotoc_md46", null ]
      ] ],
      [ "9.2 Intersection shader", "vray.html#autotoc_md47", [
        [ "9.2.1 presenz_intersection_shader.h", "vray.html#autotoc_md48", null ],
        [ "9.2.2 presenz_intersection_shader.cpp", "vray.html#autotoc_md49", null ]
      ] ],
      [ "9.3 Render output", "vray.html#autotoc_md50", [
        [ "9.3.1 presenz_render_output.h", "vray.html#autotoc_md51", null ],
        [ "9.3.2 presenz_render_output.cpp", "vray.html#autotoc_md52", null ]
      ] ]
    ] ],
    [ "Implementation in Arnold", "arnold.html", [
      [ "10.1 Camera", "arnold.html#autotoc_md53", null ],
      [ "10.2 AOV shader", "arnold.html#autotoc_md54", null ],
      [ "10.3 Intersection shader", "arnold.html#autotoc_md55", null ],
      [ "10.4 Filter", "arnold.html#autotoc_md56", null ],
      [ "10.5 Driver", "arnold.html#autotoc_md57", null ]
    ] ],
    [ "Support", "support.html", null ],
    [ "Deprecated List", "deprecated.html", null ],
    [ "Topics", "topics.html", "topics" ],
    [ "Namespace Members", "namespacemembers.html", [
      [ "All", "namespacemembers.html", "namespacemembers_dup" ],
      [ "Functions", "namespacemembers_func.html", null ],
      [ "Typedefs", "namespacemembers_type.html", null ],
      [ "Enumerations", "namespacemembers_enum.html", null ],
      [ "Enumerator", "namespacemembers_eval.html", null ]
    ] ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Structure Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", null ],
        [ "Variables", "functions_vars.html", null ],
        [ "Related Symbols", "functions_rela.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "Globals", "globals.html", [
        [ "All", "globals.html", null ],
        [ "Functions", "globals_func.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_pz_app_logger_8h.html",
"group___n_o_z___r_g_b_a.html#ga4788d82c901b9367dd5c0daff8a7616b",
"group___pz_phase_api.html#ga59c42493e6b8e40e92057362065715e1",
"struct_presen_z_1_1_detect_sample_1_1v4__0_1_1_save_data_structure.html#ac66c2e837c24a5cd822b7b42ed61558d"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';