/*
 * Copyright (c) 2016, Southwest Research Institute
 * All rights reserved.
 *
 */

#ifndef MESH_SEGMENTER_H
#define MESH_SEGMENTER_H

#include <vtk_viewer/vtk_utils.h>
#include <vtkPolyData.h>
#include <vtkTriangleFilter.h>

namespace mesh_segmenter
{
  class MeshSegmenter
  {
  public:

    /**
     * @brief setInputMesh Set the input mesh to be segmented
     * @param mesh The input mesh to operate on
     */
    void setInputMesh(vtkSmartPointer<vtkPolyData> mesh);

    /**
     * @brief getInputMesh Get the input_mesh_
     * @return The input_mesh_
     */
    vtkSmartPointer<vtkPolyData> getInputMesh(){return input_mesh_;}

    /**
     * @brief getNeighborCells Given a mesh and a target cell, find all other connecting cells
     * @param mesh The input mesh to operate on
     * @param cellId The cell id to find adjacent cells
     * @return The list of cell ids which are adjacent to the target cell
     */
    vtkSmartPointer<vtkIdList> getNeighborCells(vtkSmartPointer<vtkPolyData> mesh, int cell_id);

    /**
     * @brief segmentMesh Segments the input mesh using the desired segmentation algorithm
     */
    void segmentMesh();

    /**
     * @brief getMeshSegments Get the segments of the mesh after segmentation has been performed
     * @return The vector of mesh segments
     */
    std::vector<vtkSmartPointer<vtkPolyData> > getMeshSegments();

    /**
     * @brief segmentMesh Performs segmentation on the input mesh, starting at the start_cell id
     * @param start_cell The id of the cell to start segmentation at
     * @return The list of ids associated with the final segmentation
     */
    vtkSmartPointer<vtkIdList> segmentMesh(int start_cell);

    /**
     * @brief areNormalsNear Checks to see if two normal vectors are near each other (within a given threshold)
     * @param norm1 The first normal to check
     * @param norm2 The second normal to check
     * @param threshold The desired threshold for "nearness", 1 - must be perfectly aligned, 0 - any angle is accepted
     * @return True if the normals are near, False if they are not
     */
    bool areNormalsNear(const double* norm1, const double* norm2, double threshold);

  private:

    vtkSmartPointer<vtkPolyData> input_mesh_;  /**< The input mesh to segment */
    vtkSmartPointer<vtkTriangleFilter> triangle_filter_;  /**< VTK triangle filter for finding adjacent cells */
    std::vector<vtkSmartPointer<vtkIdList> > included_indices_;
      /**< A list of all indices which indicates which cells belong to which segmentation chuncks */
  };
}


#endif // MESH_SEGMENTER_H
