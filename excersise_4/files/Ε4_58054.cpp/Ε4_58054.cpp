#include <igl/opengl/glfw/Viewer.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include <igl/unproject_onto_mesh.h>
#include "igl/adjacency_list.h"
#include "igl/vertex_triangle_adjacency.h"
#include <igl/per_face_normals.h>
#include <igl/doublearea.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <igl/avg_edge_length.h>
#include <igl/circulation.h>
#include <igl/collapse_edge.h>
#include <igl/edge_flaps.h>
#include <igl/decimate.h>
#include <igl/shortest_edge_and_midpoint.h>
#include <igl/parallel_for.h>
#include <igl/read_triangle_mesh.h>
#include <Eigen/Core>
#include <iostream>
#include <set>
#include <igl/read_triangle_mesh.h>
#include <igl/gaussian_curvature.h>
#include <igl/massmatrix.h>
#include <igl/invert_diag.h>
#include <igl/false_barycentric_subdivision.h>
#include <igl/per_vertex_normals.h>
#include <igl/per_corner_normals.h>
#include <igl/principal_curvature.h>

int main(int argc, char* argv[])
{   //1.
    Eigen::MatrixXd C, D;
    igl::opengl::glfw::Viewer viewer;
    using namespace Eigen;
    using namespace std;
    Eigen::MatrixXd S;
    Eigen::MatrixXd S1;
    Eigen::MatrixXd S2;
    Eigen::MatrixXd S3;

    //mode = 1 -> enter pressed.
    //mode = 2 -> space pressed.
    int mode = 1;

    const auto names =
    { "fertility.off","decimated-knight.off","bumpy.off","fandisk.off" };
    const auto names2 =
    { "cow.off","3holes.off","cheburashka.off","beetle.off" };

    for (const auto& name : names)
    {
        viewer.load_mesh_from_file(std::string("res/Models/tutorial_data") + "/" + name);
    }

    unsigned int left_view, right_view, right_up_view, left_up_view;
    int obg1_id = viewer.data_list[0].id;
    int obg2_id = viewer.data_list[1].id;
    int obg3_id = viewer.data_list[2].id;
    int obg4_id = viewer.data_list[3].id;

    //New objects.
    for (const auto& name1 : names2)
    {
        viewer.load_mesh_from_file(std::string("res/Models/tutorial_data") + "/" + name1);
    }
    int obg5_id = viewer.data_list[4].id;
    int obg6_id = viewer.data_list[5].id;
    int obg7_id = viewer.data_list[6].id;
    int obg8_id = viewer.data_list[7].id;


    viewer.callback_init = [&](igl::opengl::glfw::Viewer&)
    {
        viewer.core().viewport = Eigen::Vector4f(0, 0, 640, 400);
        left_view = viewer.core_list[0].id;
        right_view = viewer.append_core(Eigen::Vector4f(640, 0, 640, 400));
        left_up_view = viewer.append_core(Eigen::Vector4f(640, 400, 640, 400));
        right_up_view = viewer.append_core(Eigen::Vector4f(0, 400, 640, 400));

        //view1
        viewer.data(obg1_id).set_visible(false, right_view);
        viewer.data(obg1_id).set_visible(false, left_up_view);
        viewer.data(obg1_id).set_visible(false, right_up_view);
        viewer.data(obg2_id).set_visible(false, left_view);
        viewer.data(obg2_id).set_visible(false, left_up_view);
        viewer.data(obg2_id).set_visible(false, right_up_view);
        viewer.data(obg3_id).set_visible(false, left_view);
        viewer.data(obg3_id).set_visible(false, right_view);
        viewer.data(obg3_id).set_visible(false, right_up_view);
        viewer.data(obg4_id).set_visible(false, left_view);
        viewer.data(obg4_id).set_visible(false, left_up_view);
        viewer.data(obg4_id).set_visible(false, right_view);

        ////Hide new objects.
        viewer.data(obg5_id).set_visible(false, left_view);
        viewer.data(obg5_id).set_visible(false, left_up_view);
        viewer.data(obg5_id).set_visible(false, right_view);
        viewer.data(obg5_id).set_visible(false, right_up_view);
        viewer.data(obg6_id).set_visible(false, left_view);
        viewer.data(obg6_id).set_visible(false, left_up_view);
        viewer.data(obg6_id).set_visible(false, right_view);
        viewer.data(obg6_id).set_visible(false, right_up_view);
        viewer.data(obg7_id).set_visible(false, left_view);
        viewer.data(obg7_id).set_visible(false, left_up_view);
        viewer.data(obg7_id).set_visible(false, right_view);
        viewer.data(obg7_id).set_visible(false, right_up_view);
        viewer.data(obg8_id).set_visible(false, left_view);
        viewer.data(obg8_id).set_visible(false, left_up_view);
        viewer.data(obg8_id).set_visible(false, right_view);
        viewer.data(obg8_id).set_visible(false, right_up_view);
        return false;
    };

    viewer.callback_key_down = [&](igl::opengl::glfw::Viewer&, unsigned int key, int mod)
    {
        if (key == GLFW_KEY_ENTER)
        {
            //camera
            viewer.core(left_view).align_camera_center(viewer.data(obg1_id).V, viewer.data(obg1_id).F);
            viewer.core(right_view).align_camera_center(viewer.data(obg2_id).V, viewer.data(obg2_id).F);
            viewer.core(left_up_view).align_camera_center(viewer.data(obg3_id).V, viewer.data(obg3_id).F);
            viewer.core(right_up_view).align_camera_center(viewer.data(obg4_id).V, viewer.data(obg4_id).F);

            viewer.data(obg1_id).set_visible(true, left_view);
            viewer.data(obg2_id).set_visible(true, right_view);
            viewer.data(obg3_id).set_visible(true, left_up_view);
            viewer.data(obg4_id).set_visible(true, right_up_view);
            viewer.data(obg5_id).set_visible(false, left_view);
            viewer.data(obg6_id).set_visible(false, right_view);
            viewer.data(obg7_id).set_visible(false, left_up_view);
            viewer.data(obg8_id).set_visible(false, right_up_view);

            mode = 1;
        }
        if (key == GLFW_KEY_SPACE)//New objects.
        {   
            //camera
            viewer.core(left_view).align_camera_center(viewer.data(obg5_id).V, viewer.data(obg5_id).F);
            viewer.core(right_view).align_camera_center(viewer.data(obg6_id).V, viewer.data(obg6_id).F);
            viewer.core(left_up_view).align_camera_center(viewer.data(obg7_id).V, viewer.data(obg7_id).F);
            viewer.core(right_up_view).align_camera_center(viewer.data(obg8_id).V, viewer.data(obg8_id).F);

            //view1
            viewer.data(obg5_id).set_visible(true, left_view);
            viewer.data(obg6_id).set_visible(true, right_view);
            viewer.data(obg7_id).set_visible(true, left_up_view);
            viewer.data(obg8_id).set_visible(true, right_up_view);
            viewer.data(obg1_id).set_visible(false, left_view);
            viewer.data(obg2_id).set_visible(false, right_view);
            viewer.data(obg3_id).set_visible(false, left_up_view);
            viewer.data(obg4_id).set_visible(false, right_up_view);

            mode = 2;
        }
        return false;
    };

    viewer.callback_post_resize = [&](igl::opengl::glfw::Viewer& v, int w, int h) 
    {
        v.core(left_view).viewport = Eigen::Vector4f(0, 0, w / 2, h / 2);
        v.core(right_up_view).viewport = Eigen::Vector4f(0, h / 2, w / 2, h / 2);
        v.core(left_up_view).viewport = Eigen::Vector4f(w / 2, h / 2, w / 2, h / 2);
        v.core(right_view).viewport = Eigen::Vector4f(w / 2, 0, w / 2, h / 2);
        return true;
    };

    //2.
    const auto update_neighbour = [&](const int vid, const int core_id)
    {
        // Compute areas.
        //area of mesh
        VectorXd area_mesh;
        double all_area_of_mesh = 0;
        double all_area_1ring = 0;
        double all_area_2ring = 0;

        igl::doublearea(viewer.data(core_id).V, viewer.data(core_id).F, area_mesh);
        area_mesh = area_mesh.array() / 2;
        for (int i = 0; i < area_mesh.size(); i++)
        {
            all_area_of_mesh += area_mesh(i);
        }
        std::cout << "\nArea of the whole mesh is: " << all_area_of_mesh << "." << std::endl;

        // Compute per-face normals of neighbourhood faces of vid.
        //A[vid] neighbours of vid.
        //VF[vid] neighbours faces of vid.
        viewer.data(core_id).clear_edges();
        Eigen::MatrixXd N_faces;
        igl::per_face_normals(viewer.data(core_id).V, viewer.data(core_id).F, N_faces);
        MatrixXd BC;
        igl::barycenter(viewer.data(core_id).V, viewer.data(core_id).F, BC);
        const RowVector3d yellow(1, 1, 0);

        //One ring.
        std::vector<std::vector<int>> A;
        igl::adjacency_list(viewer.data(core_id).F, A);

        S.setZero(viewer.data(core_id).V.rows(), 1);
        for (auto adjacentVertex : A[vid])
        {
            S(vid) += 1;
        }

        //neighbourhood faces of vid.
        std::vector<std::vector<int>> VI;
        std::vector<std::vector<int>> VF;
        S1.setZero(viewer.data(core_id).V.rows(), 1);
        igl::vertex_triangle_adjacency(viewer.data(core_id).V.rows(), viewer.data(core_id).F, VF, VI);

        for (auto adjacentFace : VF[vid])
        {
            S1(vid) += 1;
        }
        //std::cout << "\nVertex " << vid << " has " << S1(vid) << " neighbour faces." << std::endl;
        for (int i = 0; i < S1(vid); i++)
        {
            all_area_1ring += area_mesh(VF[vid][i]);
            viewer.data(core_id).add_edges(BC.row(VF[vid][i]), BC.row(VF[vid][i]) + N_faces.row(VF[vid][i]), yellow);
            //std::cout << "face " << i << " is " << VF[vid][i] << "." << std::endl;
        }
       std::cout << "Area of 1-ring is: " << (all_area_1ring / all_area_of_mesh) * 100 << "% of the area of the whole mesh." << std::endl;
       
        //Two ring.
        //neighbourhood vertexes of neighbourhood vertexes of vid.
        for (int m = 0; m < S(vid); m++)
        {
            int vertex = A[vid][m];
            std::vector<std::vector<int>> B;
            igl::adjacency_list(viewer.data(core_id).F, B);
            S2.setZero(viewer.data(core_id).V.rows(), 1);

            for (auto adjacentVertex : B[vertex])
            {
                S2(vertex) += 1;
            }
            //std::cout << "\nVertex " << m << " has " << S2(vertex) << " neighbours." << std::endl;
            //for (int i = 0; i < S2(vertex); i++)
            //{
            //    //std::cout << "neighbour " << i << " is " << B[vertex][i] << "." << std::endl;
            //}
        }

        C = Eigen::MatrixXd::Constant(viewer.data(core_id).F.rows(), 3, 1);
        //neighbourhood faces of neighbors of vid.
        //neighbourhood vertexes of neighbourhood vertexes of vid.
        for (int m = 0; m < S(vid); m++)
        {
            int vertex = A[vid][m];
            std::vector<std::vector<int>> B;
            igl::adjacency_list(viewer.data(core_id).F, B);
            S2.setZero(viewer.data(core_id).V.rows(), 1);
            std::vector<std::vector<int>> VI1;
            std::vector<std::vector<int>> VF1;

            for (auto adjacentVertex : B[vertex]) 
            {
                S2(vertex) += 1;
                igl::vertex_triangle_adjacency(viewer.data(core_id).V.rows(), viewer.data(core_id).F, VF1, VI1);
            }
            //std::cout << "\nFace " << m << " has " << S2(vertex) << " neighbour faces." << std::endl;
            for (int i = 0; i < S2(vertex); i++)
            {
                all_area_2ring += area_mesh(VF1[vertex][i]);
                viewer.data(core_id).add_edges(BC.row(VF1[vertex][i]), BC.row(VF1[vertex][i]) + N_faces.row(VF1[vertex][i]), yellow);
                //std::cout << "neighbour face " << i << " is " << VF1[vertex][i] << "." << std::endl;
            }
            
            //Colors
            for (int i = 0; i < S2(A[vid][m]); i++)
            {
                // paint hit green
                C.row(VF1[A[vid][m]][i]) << 0, 1, 0;
            }

            for (int i = 0; i < S1(vid); i++)
            {
                // paint hit red
                C.row(VF[vid][i]) << 1, 0, 0;
            }
        }
        std::cout << "Area of 2-ring is: " << (all_area_2ring / all_area_of_mesh) * 100 << "% of the area of the whole mesh." << std::endl;
        viewer.data(core_id).set_colors(C);
    };

    // Plot a distance when a vertex is picked
    //vid,fid.
    int id;
    int object;
    viewer.callback_mouse_down =
        [&](igl::opengl::glfw::Viewer& viewer, int, int)->bool
    {
        viewer.select_hovered_core();
        id = viewer.core_list[viewer.selected_core_index].id;

        if (mode == 1)
        {
            if (viewer.selected_core_index == 0)
            {
                object = 0;
            }
            else if (viewer.selected_core_index == 1)
            {
                object = 1;
            }
            else if (viewer.selected_core_index == 2)
            {
                object = 2;
            }
            else if (viewer.selected_core_index == 3)
            {
                object = 3;
            }
        }
        else if (mode == 2)
        {
            if (viewer.selected_core_index == 0)
            {
                object = 4;
            }
            else if (viewer.selected_core_index == 1)
            {
                object = 5;
            }
            else if (viewer.selected_core_index == 2)
            {
                object = 6;
            }
            else if (viewer.selected_core_index == 3)
            {
                object = 7;
            }
        }

        int fid;
        Eigen::Vector3f bc;
        double x = viewer.current_mouse_x;
        double y = (viewer.core().viewport(3) * 2 - viewer.current_mouse_y);

        if (igl::unproject_onto_mesh(
            Eigen::Vector2f(x, y),
            viewer.core().view,
            viewer.core().proj,
            viewer.core().viewport,
            (viewer.data(object).V),
            (viewer.data(object).F),
            fid,
            bc))
        {
            int max;
            bc.maxCoeff(&max);
            int vid = (viewer.data(object).F)(fid, max);
            std::cout << "\n\n\nNew point! " << std::endl;
            std::cout << "Click space to load new objects." << std::endl;
            std::cout << "Click enter to load old objects." << std::endl;
            //std::cout << "Face " << fid << std::endl;
            update_neighbour(vid, object);

            // Compute areas.
            //area of mesh
            VectorXd area_mesh;
            double all_area_of_mesh = 0;
            double all_area_of_fid = 0;

            igl::doublearea(viewer.data(object).V, viewer.data(object).F, area_mesh);
            area_mesh = area_mesh.array() / 2;
            for (int i = 0; i < area_mesh.size(); i++)
            {
                all_area_of_mesh += area_mesh(i);
            }
            //area of fid.
            all_area_of_fid = area_mesh(fid);
            std::cout << "Area of fid is: " << (all_area_of_fid / all_area_of_mesh) * 100 << "% of the area of the whole mesh." << std::endl;

            return true;
        }
        return false;
    };
    viewer.data(object).set_colors(C);

    //3.
    //Default MENU. 
    viewer.select_hovered_core();
    // Attach a menu plugin
    igl::opengl::glfw::imgui::ImGuiMenu menu;
    viewer.plugins.push_back(&menu);
    // Customize the menu
    double doubleVariable = 0.1f; // Shared between two menus
    // Add content to the default menu window
    menu.callback_draw_viewer_menu = [&]()
    {   
        // Draw parent menu content
        menu.draw_viewer_menu();
        if (mode == 1)
        {
            if (viewer.selected_core_index == 0)
            {
                viewer.selected_data_index = 0;
            }
            else if (viewer.selected_core_index == 1)
            {
                viewer.selected_data_index = 1;
            }
            else if (viewer.selected_core_index == 2)
            {
                viewer.selected_data_index = 2;
            }
            else if (viewer.selected_core_index == 3)
            {
                viewer.selected_data_index = 3;
            }
        }
        else if (mode == 2)
        {
            if (viewer.selected_core_index == 0)
            {
                viewer.selected_data_index = 4;
            }
            else if (viewer.selected_core_index == 1)
            {
                viewer.selected_data_index = 5;
            }
            else if (viewer.selected_core_index == 2)
            {
                viewer.selected_data_index = 6;
            }
            else if (viewer.selected_core_index == 3)
            {
                viewer.selected_data_index = 7;
            }
        }
        //Add new group //Default MENU.
        if (ImGui::CollapsingHeader("New Group", ImGuiTreeNodeFlags_DefaultOpen))
        {
            // Expose variable directly ...
            ImGui::InputDouble("double", &doubleVariable, 0, 0, "%.4f");
            // ... or using a custom callback
            static bool boolVariable = true;
            if (ImGui::Checkbox("bool", &boolVariable))
            {
                // do something
                std::cout << "boolVariable: " << std::boolalpha << boolVariable << std::endl;
            }
            // Expose an enumeration type
            enum Orientation { Up = 0, Down, Left, Right };
            static Orientation dir = Up;
            ImGui::Combo("Direction", (int*)(&dir), "Up\0Down\0Left\0Right\0\0");
            // We can also use a std::vector<std::string> defined dynamically
            static int num_choices = 3;
            //static int selectedViewport = 3;
            static std::vector<std::string> choices;
            static int idx_choice = 0;
            if (ImGui::InputInt("Num letters", &num_choices))
            {
                num_choices = std::max(1, std::min(26, num_choices));
            }
            if (num_choices != (int)choices.size())
            {
                choices.resize(num_choices);
                for (int i = 0; i < num_choices; ++i)
                    choices[i] = std::string(1, 'A' + i);
                if (idx_choice >= num_choices)
                    idx_choice = num_choices - 1;
            }
            ImGui::Combo("Letter", &idx_choice, choices);
            // Add a button
            if (ImGui::Button("Print Hello", ImVec2(-1, 0)))
            {
                std::cout << "Hello\n";
            }

            //NEW MENU.
            //a)
            static int selectedViewport = 0;
            //ImGui::InputInt("selectedViewport", &viewer.data_list[viewer.selected_core_index].id);
            if (ImGui::InputInt("selectedViewport", &selectedViewport))
            {
                selectedViewport = std::max(0, std::min(3, selectedViewport));
            }
            
            //b)
            int index;

            //Find the index you want.
            if (mode == 1)
            {
                if (selectedViewport == 0)
                {
                    index = 0;
                }
                else if (selectedViewport == 1)
                {
                    index = 1;
                }
                else if (selectedViewport == 2)
                {
                    index = 2;
                }
                else if (selectedViewport == 3)
                {
                    index = 3;
                }
            }
            else if (mode == 2)
            {
                if (selectedViewport == 0)
                {
                    index = 4;
                }
                else if (selectedViewport == 1)
                {
                    index = 5;
                }
                else if (selectedViewport == 2)
                {
                    index = 6;
                }
                else if (selectedViewport == 3)
                {
                    index = 7;
                }
            }

            if (ImGui::Button("decimate", ImVec2(-1, 0)))
            {
                MatrixXd U1;
                MatrixXi G1;
                VectorXi J;
                igl::decimate(viewer.data(index).V, viewer.data(index).F, 1000, U1, G1, J);
                viewer.data(index).clear();
                viewer.data(index).set_mesh(U1, G1);
                viewer.data(index).set_face_based(true);
            }
            if (ImGui::Button("subdivide", ImVec2(-1, 0)))
            {
                MatrixXd U2;
                MatrixXi G2;
                igl::false_barycentric_subdivision(Eigen::MatrixXd(viewer.data(index).V), Eigen::MatrixXi(viewer.data(index).F), U2, G2);
                viewer.data(index).clear();
                viewer.data(index).set_mesh(U2, G2);
                viewer.data(index).set_face_based(true);
            }

            //c)
            static bool Gaussian_Curvature = false; 
            static bool Curvature_Directions = false;
            
			if (ImGui::Checkbox("Gaussian Curvature", &Gaussian_Curvature))
			{
                MatrixXd V1 = viewer.data(index).V;
                MatrixXi F1 = viewer.data(index).F;
                VectorXd K;

                // Compute integral of Gaussian curvature, #V by 1
                igl::gaussian_curvature(V1, F1, K);
                SparseMatrix<double> M, Minv;
                igl::massmatrix(V1, F1, igl::MASSMATRIX_TYPE_DEFAULT, M);
                igl::invert_diag(M, Minv);
                // Divide by area to get integral average
                K = (Minv * K).eval();
                viewer.data(index).clear();
                viewer.data(index).set_mesh(V1, F1);
                viewer.data(index).set_data(K);
			}

			if (ImGui::Checkbox("Curvature Directions", &Curvature_Directions))
			{
                MatrixXd V = viewer.data(index).V;
                MatrixXi F = viewer.data(index).F;

				// Compute integral of Gaussian curvature, #V by 1
				// Alternative discrete mean curvature
				MatrixXd HN;
				SparseMatrix<double> L, M, Minv;
				igl::cotmatrix(V, F, L);
				igl::massmatrix(V, F, igl::MASSMATRIX_TYPE_VORONOI, M);
				igl::invert_diag(M, Minv);
				// Laplace-Beltrami of position
				HN = -Minv * (L * V);
				// Extract magnitude as mean curvature
				VectorXd H = HN.rowwise().norm();
				// Compute curvature directions via quadric fitting
				MatrixXd PD1, PD2;
				VectorXd PV1, PV2;
				igl::principal_curvature(V, F, PD1, PD2, PV1, PV2);
				// mean curvature
				H = 0.5 * (PV1 + PV2);
				viewer.data(index).clear();
				viewer.data(index).set_mesh(V, F);
				viewer.data(index).set_data(H);
				// Average edge length for sizing
				const double avg = igl::avg_edge_length(V, F);
				// Draw a blue segment parallel to the minimal curvature direction
				const RowVector3d red(0.8, 0.2, 0.2), blue(0.2, 0.2, 0.8);
				viewer.data(index).add_edges(V + PD1 * avg, V - PD1 * avg, blue);
				// Draw a red segment parallel to the maximal curvature direction
				viewer.data(index).add_edges(V + PD2 * avg, V - PD2 * avg, red);
				// Hide wireframe
				viewer.data(index).show_lines = false;
			}

            //d)
            MatrixXd V = viewer.data(index).V;
            MatrixXi F = viewer.data(index).F;
            static bool Surface_classification = false;
            Eigen::MatrixXd C1;
            C1 = Eigen::MatrixXd::Constant(V.rows(), 3, 1);
            if (ImGui::Checkbox("Surface classification", &Surface_classification))
            {
                MatrixXd PD1, PD2;
                VectorXd k1, k2;
                igl::principal_curvature(V, F, PD1, PD2, k1, k2);
                for (int i=0; i < k1.size(); i++)
                {
                    if (k1[i] * k2[i] > 0)//Elliptic.
                    {
                        C1.row(i) << 1, 0, 0;
                    }
                    else if (k1[i] * k2[i] == 0)//Parabolic.
                    {
                        C1.row(i) << 0, 1, 0;
                    }
                    else if (k1[i] * k2[i] < 0)//Hyperbolic.
                    {
                        C1.row(i) << 0, 0, 1;
                    }
                } 
                viewer.data(index).set_colors(C1);

            }
        }
    };

    // Draw additional windows
    menu.callback_draw_custom_window = [&]()
    {
        // Define next window position + size
        ImGui::SetNextWindowPos(ImVec2(180.f * menu.menu_scaling(), 10), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(200, 160), ImGuiCond_FirstUseEver);
        ImGui::Begin(
            "New Window", nullptr,
            ImGuiWindowFlags_NoSavedSettings
        );
        // Expose the same variable directly ...
        ImGui::PushItemWidth(-80);
        ImGui::DragScalar("double", ImGuiDataType_Double, &doubleVariable, 0.1, 0, 0, "%.4f");
        ImGui::PopItemWidth();
        static std::string str = "Excersise 3";
        ImGui::InputText("Name", str);
        ImGui::End();
    };
    viewer.data().add_label(viewer.data().V.row(0) + viewer.data().V_normals.row(0).normalized() * 0.005, "Hello World!");

    return viewer.launch();
}