
#include <iostream>
#include <fstream>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

/**
 * @brief Saving point clouds data as ply file
 * @param [in] filename : filename for saving point clouds (the extention should be .ply)
 * @param [in] vertices : list of vertex point
 * @param [in] colors   : list of vertex color
 * @return Success:true, Failure:false
 */
bool savePointCloudsPLY(std::string filename, std::vector<cv::Vec3f>& vertices, std::vector<cv::Vec3b>& colors)
{
    std::ofstream fout;
    fout.open( filename.c_str() );
    if (fout.fail()){
        std::cerr << "file open error:" << filename << std::endl;
        return false;
    }
    
    int pointNum = vertices.size();

    fout << "ply" << std::endl;
    fout << "format ascii 1.0" << std::endl;
    fout << "element vertex " << pointNum << std::endl;
    fout << "property float x" << std::endl;
    fout << "property float y" << std::endl;
    fout << "property float z" << std::endl;
    fout << "property uchar red" << std::endl;
    fout << "property uchar green" << std::endl;
    fout << "property uchar blue" << std::endl;
    fout << "property uchar alpha" << std::endl;
    fout << "end_header" << std::endl;
    
    for(int i=0; i<pointNum; i++){
        cv::Vec3f& vertex = vertices[i];
        cv::Vec3b& col = colors[i];
        
        fout << vertex[0] << " " << vertex[1] << " " << vertex[2] << " "<<  static_cast<int>(col[2]) << " " << static_cast<int>(col[1]) << " " << static_cast<int>(col[0]) << " " << 255  << std::endl;
    }
    
    fout.close();
    
    return true;
}


/**
 * @brief Loading camera pose file (6Dof rigid transformation)
 * @param [in]  filename : filename for loading text file
 * @param [out] rotMat   : rotation matrix
 * @param [out] transMat : translation vector
 * @return Success:true, Failure:false
 */
bool loadCameraPose(std::string filename, cv::Matx33f& rotMat, cv::Vec3f& transVec)
{
    std::ifstream fin;
    fin.open( filename.c_str() );
    if (fin.fail()){
        std::cerr << "file open error:" << filename << std::endl;
        return false;
    }
    
    // Loading rotation matrix and translation vector
    for(int y=0; y<3; y++){
        for(int x=0; x<3; x++){
            fin >> rotMat(y, x);
        }
        fin >> transVec(y);
        
    }
    return true;
}

int main(int argc, char* argv[])
{
    // Loading depth image and color image (need to put correct path on your environment)
    std::string depthFilename = "../data/modeling/depth/depth0.png";
    std::string colorFilename = "../data/modeling/color/color0.png";
    cv::Mat depthImg = cv::imread(depthFilename, CV_LOAD_IMAGE_UNCHANGED );
    cv::Mat colorImg = cv::imread(colorFilename, CV_LOAD_IMAGE_UNCHANGED );
    
    // Loading camera pose (need to put correct path on your environment)
    std::string poseFilename = "../data/modeling/pose/pose0.txt";
    cv::Matx33f rotMat; // rotation matrix
    cv::Vec3f transVec; // translation vector
    loadCameraPose(poseFilename, rotMat, transVec);
    std::cout << "Rotation matrix" << std::endl << rotMat << std::endl;
    std::cout << "Translation vector" << std::endl << transVec << std::endl;
    
    // Setting camera intrinsic parameters of depth camera
    float focal = 570.f;  // focal length
    float px    = 319.5f; // principal point x
    float py    = 239.5f; // principal point y
    
    // Data for point clouds consisted of 3D points and their colors
    std::vector<cv::Vec3f> vertices; // 3D points
    std::vector<cv::Vec3b> colors;   // color of the points
    
    // Create point clouds from depth image and color image using camera intrinsic parameters
    // (1) Compute 3D point from depth values and pixel locations on depth image using camera intrinsic parameters.
    // (2) Translate 3D point in local coordinate system to 3D point in global coordinate system using camera pose. (you can skip this process during task (c) in the instruction sheet. )
    // (3) Add the 3D point to vertices in point clouds data.
    // (4) Also compute the color of 3D point and add it to colors in point clouds data.
    
    
    
    
    
    
    
    // Save point clouds
    savePointCloudsPLY("pointClouds.ply", vertices, colors);
    
    
    return 0;
}
