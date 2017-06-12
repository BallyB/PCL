#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/io/ply_io.h>
int
 main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZ>);


   if (pcl::io::loadPLYFile<pcl::PointXYZ> ("/home/adrien/Documents/Projets/Datasets/Bunny Model/bunny/bun000.ply", *cloud_in) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read file file1.ply \n");
    return (-1);
  }

  std::cout << "File 1," << cloud_in->points.size () << " data points to input:"
      << std::endl;
  for (size_t i = 0; i < cloud_in->points.size (); ++i) std::cout << "    " <<
      cloud_in->points[i].x << " " << cloud_in->points[i].y << " " <<
      cloud_in->points[i].z << std::endl;
  //*cloud_out = *cloud_in;
  std::cout << "size:" << cloud_in->points.size() << std::endl;

  if (pcl::io::loadPCDFile<pcl::PointXYZ> ("/home/adrien/Documents/Projets/Datasets/Bunny Model/bunny/bun045.ply", *cloud_out) == -1) //* load the file
  {
    PCL_ERROR ("Couldn't read file file2.ply \n");
    return (-1);
  }

/*  for (size_t i = 0; i < cloud_in->points.size (); ++i)
    cloud_out->points[i].x = cloud_in->points[i].x + 0.7f;*/
  std::cout << "File 2," << cloud_out->points.size () << " data points to input:"
      << std::endl;
  for (size_t i = 0; i < cloud_out->points.size (); ++i)
    std::cout << "    " << cloud_out->points[i].x << " " <<
      cloud_out->points[i].y << " " << cloud_out->points[i].z << std::endl;
  std::cout << "size:" << cloud_out->points.size() << std::endl;

  pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
  icp.setInputCloud(cloud_in);
  icp.setInputTarget(cloud_out);
  pcl::PointCloud<pcl::PointXYZ> Final;
  icp.align(Final);
  std::cout << "has converged:" << icp.hasConverged() << " score: " <<
  icp.getFitnessScore() << std::endl;
  std::cout << icp.getFinalTransformation() << std::endl;

 return (0);
}
