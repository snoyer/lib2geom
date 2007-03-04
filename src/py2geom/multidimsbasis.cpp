/*
 * Copyright 2006, 2007 Aaron Spike <aaron@ekips.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it either under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * (the "LGPL") or, at your option, under the terms of the Mozilla
 * Public License Version 1.1 (the "MPL"). If you do not alter this
 * notice, a recipient may use your version of this file under either
 * the MPL or the LGPL.
 *
 * You should have received a copy of the LGPL along with this library
 * in the file COPYING-LGPL-2.1; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * You should have received a copy of the MPL along with this library
 * in the file COPYING-MPL-1.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY
 * OF ANY KIND, either express or implied. See the LGPL or the MPL for
 * the specific language governing rights and limitations.
 *
 */

#include <boost/python.hpp>

#include "helpers.h"
#include "../multidim-sbasis.h"

using namespace boost::python;

typedef Geom::MultidimSBasis<2> MultidimSBasis2;
typedef Geom::MultidimSBasis<3> MultidimSBasis3;


void wrap_multidimsbasis() {
    class_<MultidimSBasis2>("MultidimSBasis2")
        .def("__getitem__", python_getitem<MultidimSBasis2,Geom::SBasis,2>)
        .def("size", &MultidimSBasis2::size)
        .def("tail_error", &MultidimSBasis2::tail_error)
        .def("is_finite", &MultidimSBasis2::is_finite)
        .def(self + self)
        .def(self - self)
        .def(self + Geom::Point())
        .def(self - Geom::Point())
        .def(double() * self)
        .def(self += self)
        .def(self += Geom::Point())
        .def(self -= Geom::Point())
        .def(self *= double())
    ;
    class_<MultidimSBasis3>("MultidimSBasis3")
        .def("__getitem__", python_getitem<MultidimSBasis2,Geom::SBasis,3>)
        .def("size", &MultidimSBasis3::size)
        .def("tail_error", &MultidimSBasis3::tail_error)
        .def("is_finite", &MultidimSBasis3::is_finite)
        .def(self + self)
        .def(self - self)
        .def(double() * self)
        .def(self += self)
        .def(self *= double())
    ;
};

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :