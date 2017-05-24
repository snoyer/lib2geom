/*
 * Copyright 2009 Ricardo Lafuente <r@sollec.org>
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
#include <boost/python/implicit.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "py2geom.h"
#include "helpers.h"

#include <2geom/point.h>
#include <2geom/sbasis.h>
#include <2geom/exception.h>

using namespace boost::python;

struct Point_from_tuple{
    Point_from_tuple(){
        boost::python::converter::registry::push_back(
            &convertible,
            &construct,
            boost::python::type_id<Geom::Point>()
        );
    }

    // Determine if obj_ptr can be converted in a QString
    static void* convertible(PyObject* obj_ptr){
        if(!PyTuple_Check(obj_ptr)) return 0;

        const boost::python::tuple tuple = boost::python::extract<boost::python::tuple>(obj_ptr);
        if(boost::python::len(tuple) != 2) return 0;

        return obj_ptr;
    }

    // Convert obj_ptr into a QString
    static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
        const boost::python::tuple tuple = boost::python::extract<boost::python::tuple>(obj_ptr);

        void* storage = (
            (boost::python::converter::rvalue_from_python_storage<Geom::Point>*)data
        )->storage.bytes;

        new (storage) Geom::Point(
            boost::python::extract<double>(tuple[0]),
            boost::python::extract<double>(tuple[1])
        );
        data->convertible = storage;
    }
};


void wrap_etc() {
    // needed for roots
    class_<DoubleVec >("DoubleVec")
        .def(vector_indexing_suite<std::vector<double> >())
    ;
    class_<PointVec>("PointVec")
        .def(vector_indexing_suite<std::vector<Geom::Point> >())
    ;
    // sbasis is a subclass of
    class_<LinearVec >("LinearVec")
        .def(vector_indexing_suite<std::vector<Geom::Linear> >())
    ;

    Point_from_tuple();
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
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
