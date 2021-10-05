#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <algorithm>
#include <cmath>
#include <vector>
#include<string>
#include "line.h"
#include "Triangle.h"

#include <glew.h>    //include glew.h before glfw.h
#include <glfw3.h>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace glm;
using namespace boost;

// can be changed to any screen size desired
#define SCREEN_WIDTH 1280        
#define SCREEN_HEIGHT 720

// struct to represent a point
struct Point {
	double x, y;
};

// check if it is the same line
bool compare(const Line& a, const Line& b)
{
	return (a.x1 == b.x1) && (a.y1 == b.y1) && (a.x2 == b.x2) && (a.y2 == b.y2);
}


// calculate t derived from https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
vector<Line> calculateT(Line line1, Line line2)
{
	vector<Line> lines;
	Line line;
	// calculate intersection lines for t=0, t=calc, and t=1
	double t = (((line1.x1 - line2.x1) * (line2.y1 - line2.y2) - (line1.y1 - line2.y1) * (line2.x1 - line2.x2)) /
		((line1.x1 - line1.x2) * (line2.y1 - line2.y2) - (line1.y1 - line1.y2) * (line2.x1 - line2.x2)));
	// if theres an intersection
	if ((0.0 < t) && (t < 1.0)) {
		// push first point to intersection point
		line.x1 = line1.x1;
		line.y1 = line1.y1;
		line.x2 = line1.x1 + t * (line1.x2 - line1.x1);
		line.y2 = line1.y1 + t * (line1.y2 - line1.y1);
		line.color = 1.0;
		lines.push_back(line);
		// push intersection point to second point
		line.x1 = line1.x1 + t * (line1.x2 - line1.x1);
		line.y1 = line1.y1 + t * (line1.y2 - line1.y1);
		line.x2 = line1.x2;
		line.y2 = line1.y2;
		lines.push_back(line);
		line.color = 1.0;
		// else push first point to second point
	}
	else {
		line.x1 = line1.x1;
		line.y1 = line1.y1;
		line.x2 = line1.x2;
		line.y2 = line1.y2;
		line.color = 0.0;
		lines.push_back(line);
	}

	return lines;
}

vector<Line> logicFunc(vector<Line> lines)
{
	vector<Line> intersections;
	vector<Line> singleLine;

	//first triangle
	singleLine = calculateT(lines[0], lines[1]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[0], lines[2]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[1], lines[2]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });

	// check for all possible intersecting lines between the two triangles
	singleLine = calculateT(lines[0], lines[3]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[0], lines[4]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[0], lines[5]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[1], lines[3]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[1], lines[4]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[1], lines[5]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[2], lines[3]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[2], lines[4]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[2], lines[5]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[3], lines[0]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[4], lines[0]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[5], lines[0]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[3], lines[1]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[4], lines[1]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[5], lines[1]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[3], lines[2]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[4], lines[2]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[5], lines[2]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });

	// second triangle
	singleLine = calculateT(lines[3], lines[4]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[3], lines[5]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	singleLine = calculateT(lines[4], lines[5]);
	for (auto i : singleLine)
		intersections.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });

	return intersections;
}

// create new randomly generated triangles and preform intersection logic on them
void newRandomTriangles(vector<Line> &orgTriangles, vector<Line> &orgIntersections, vector<Line> &orgColor)
{
	// set seed
	srand(time(NULL));

	// clear 'original' triangles set
	orgIntersections.clear();
	orgTriangles.clear();
	orgColor.clear();

	// new coords for triangle 1
	double t1NewAx = rand() % SCREEN_WIDTH;
	double t1NewBx = rand() % SCREEN_WIDTH;
	double t1NewCx = rand() % SCREEN_WIDTH;
	double t1NewAy = rand() % SCREEN_HEIGHT;
	double t1NewBy = rand() % SCREEN_HEIGHT;
	double t1NewCy = rand() % SCREEN_HEIGHT;

	// new coords for triangle 2
	double t2NewAx = rand() % SCREEN_WIDTH;
	double t2NewBx = rand() % SCREEN_WIDTH;
	double t2NewCx = rand() % SCREEN_WIDTH;
	double t2NewAy = rand() % SCREEN_HEIGHT;
	double t2NewBy = rand() % SCREEN_HEIGHT;
	double t2NewCy = rand() % SCREEN_HEIGHT;

	// replace triangle 1
	Line t1a(t1NewAx, t1NewAy, t1NewBx, t1NewBy, 0.0);
	orgTriangles.push_back(t1a);
	Line t1b(t1NewBx, t1NewBy, t1NewCx, t1NewCy, 0.0);
	orgTriangles.push_back(t1b);
	Line t1c(t1NewCx, t1NewCy, t1NewAx, t1NewAy, 0.0);
	orgTriangles.push_back(t1c);
	// replace triangle 2
	Line t2a(t2NewAx, t2NewAy, t2NewBx, t2NewBy, 0.0);
	orgTriangles.push_back(t2a);
	Line t2b(t2NewBx, t2NewBy, t2NewCx, t2NewCy, 0.0);
	orgTriangles.push_back(t2b);
	Line t2c(t2NewCx, t2NewCy, t2NewAx, t2NewAy, 0.0);
	orgTriangles.push_back(t2c);

	// give coordinates of newly generated triangles
	cout << "Triangle 1:" << endl;
	cout << "X: " << t1NewAx << "Y1: " << t1NewAy << endl;
	cout << "X: " << t1NewBx << "Y1: " << t1NewBy << endl;
	cout << "X: " << t1NewCx << "Y1: " << t1NewCy << endl;

	cout << "Triangle 2:" << endl;
	cout << "X: " << t2NewAx << "Y1: " << t2NewAy << endl;
	cout << "X: " << t2NewBx << "Y1: " << t2NewBy << endl;
	cout << "X: " << t2NewCx << "Y1: " << t2NewCy << endl;


	// preform intersection logic on the new triangles
	orgIntersections = logicFunc(orgTriangles);

	// remove duplicates
	orgIntersections.erase(unique(orgIntersections.begin(), orgIntersections.end(), compare), orgIntersections.end());
	for (auto i : orgIntersections) {
		// cout << "x1: " << i.x1 << ", y1: " << i.y1 << " x2: " << i.x2 << ", y2: " << i.y2 << ", color: " << i.color << endl;
		if (i.color == 1)
			orgColor.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	}

	// no lines intersect
	if (((t1NewAx < t2NewAx) && (t1NewAx < t2NewBx) && (t1NewAx < t2NewCx) &&
		(t1NewBx < t2NewAx) && (t1NewBx < t2NewBx) && (t1NewBx < t2NewCx) &&
		(t1NewCx < t2NewAx) && (t1NewCx < t2NewCx) && (t1NewCx < t2NewCx) &&
		(t1NewAy < t2NewAy) && (t1NewAy < t2NewBy) && (t1NewAy < t2NewCy) &&
		(t1NewBy < t2NewAy) && (t1NewBy < t2NewBy) && (t1NewBy < t2NewCy) &&
		(t1NewCy < t2NewAy) && (t1NewCy < t2NewCy) && (t1NewCy < t2NewCy)) ||
		((t1NewAx > t2NewAx) && (t1NewAx > t2NewBx) && (t1NewAx > t2NewCx) &&
			(t1NewBx > t2NewAx) && (t1NewBx > t2NewBx) && (t1NewBx > t2NewCx) &&
			(t1NewCx > t2NewAx) && (t1NewCx > t2NewCx) && (t1NewCx > t2NewCx) &&
			(t1NewAy > t2NewAy) && (t1NewAy > t2NewBy) && (t1NewAy > t2NewCy) &&
			(t1NewBy > t2NewAy) && (t1NewBy > t2NewBy) && (t1NewBy > t2NewCy) &&
			(t1NewCy > t2NewAy) && (t1NewCy > t2NewCy) && (t1NewCy > t2NewCy)))
		orgColor.clear();
}

// Fast way to find intersection point of two line segments
// derived from https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
	float p2_x, float p2_y, float p3_x, float p3_y, float* i_x, float* i_y)
{
	float s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
	s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

	float s, t;
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		// Collision detected
		if (i_x != NULL)
			*i_x = p0_x + (t * s1_x);
		if (i_y != NULL)
			*i_y = p0_y + (t * s1_y);
		return 1;
	}

	return 0; // No collision
}


int main()
{
	glewExperimental = true;
	

	// Check of glfw initializes
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initalize GLFW\n");
		return -1;
	}

	// Create window
	GLFWwindow* window;
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test", NULL, NULL);
	// Check window can be made
	if (window == NULL) 
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW


	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) 
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	GLuint VertexArrayID;           // Create Vertex Array Object
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// allows us to have standard coordinate system relative to SCREEN_WIDTH x SCREEN_HEIGHT
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// create example triangles for the program to open up and display
	vector<Line> lines;
	vector<Line> intersections;
	// Triangle one
	Line t1a(221, 447, 463, 152, 0.0);
	lines.push_back(t1a);
	Line t1b(463, 152, 1214, 490, 0.0);
	lines.push_back(t1b);
	Line t1c(1214, 490, 221, 447, 0.0);
	lines.push_back(t1c);
	// Triangle two
	Line t2a(1269, 467, 1078, 80, 0.0);
	lines.push_back(t2a);
	Line t2b(1078, 80, 226, 328, 0.0);
	lines.push_back(t2b);
	Line t2c(226, 328, 1269, 467, 0.0);
	lines.push_back(t2c);

	// find intersections of example triangles
	intersections = logicFunc(lines);
	vector<Line> color;

	// remove duplicates intersections
	intersections.erase(unique(intersections.begin(), intersections.end(), compare), intersections.end());
	for (auto i : intersections) {
		// cout << "x1: " << i.x1 << ", y1: " << i.y1 << " x2: " << i.x2 << ", y2: " << i.y2 << ", color: " << i.color << endl;
		if (i.color == 1)
			color.push_back({ i.x1, i.y1, i.x2, i.y2, i.color });
	}

	for (auto i : color)
		cout << "x1: " << i.x1 << ", y1: " << i.y1 << " x2: " << i.x2 << ", y2: " << i.y2 << ", color: " << i.color << endl;

	

	while (!glfwWindowShouldClose(window))
	{
		// draw two new random triangles
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1.0, 1.0, 1.0);
			newRandomTriangles(lines, intersections, color);

			// draw triangles
			for (auto i : lines)
			{
				glBegin(GL_LINES);
				glVertex2f(i.x1, i.y1);
				glVertex2f(i.x2, i.y2);
				glEnd();
			}
		}

		// redraw original shape with no augmentations
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1.0, 1.0, 1.0); // non-intersection color white

			//draw triangles
			for (auto i : lines)
			{
				glBegin(GL_LINES);
				glVertex2f(i.x1, i.y1);
				glVertex2f(i.x2, i.y2);
				glEnd();
			}
		}
		
		// display intersections in red
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			int intersect;
			float x = 0.0;
			float y = 0.0;

			// compare each line in both triangles together to determine intersection
			intersect = get_line_intersection(lines[0].x1, lines[0].y1, lines[0].x2, lines[0].y2, lines[3].x1, lines[3].y1, lines[3].x2, lines[3].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[0].x1, lines[0].y1);
				glVertex2f(lines[0].x2, lines[0].y2);
				glVertex2f(lines[3].x1, lines[3].y1);
				glVertex2f(lines[3].x2, lines[3].y2);
				glEnd();
			}

			intersect = get_line_intersection(lines[0].x1, lines[0].y1, lines[0].x2, lines[0].y2, lines[4].x1, lines[4].y1, lines[4].x2, lines[4].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[0].x1, lines[0].y1);
				glVertex2f(lines[0].x2, lines[0].y2);
				glVertex2f(lines[4].x1, lines[4].y1);
				glVertex2f(lines[4].x2, lines[4].y2);
				glEnd();
			}

			intersect = get_line_intersection(lines[0].x1, lines[0].y1, lines[0].x2, lines[0].y2, lines[5].x1, lines[5].y1, lines[5].x2, lines[5].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[0].x1, lines[0].y1);
				glVertex2f(lines[0].x2, lines[0].y2);
				glVertex2f(lines[5].x1, lines[5].y1);
				glVertex2f(lines[5].x2, lines[5].y2);
				glEnd();
			}

			intersect = get_line_intersection(lines[1].x1, lines[1].y1, lines[1].x2, lines[1].y2, lines[3].x1, lines[3].y1, lines[3].x2, lines[3].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[1].x1, lines[1].y1);
				glVertex2f(lines[1].x2, lines[1].y2);
				glVertex2f(lines[3].x1, lines[3].y1);
				glVertex2f(lines[3].x2, lines[3].y2);
				glEnd();
			}

			intersect = get_line_intersection(lines[1].x1, lines[1].y1, lines[1].x2, lines[1].y2, lines[4].x1, lines[4].y1, lines[4].x2, lines[4].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[1].x1, lines[1].y1);
				glVertex2f(lines[1].x2, lines[1].y2);
				glVertex2f(lines[4].x1, lines[4].y1);
				glVertex2f(lines[4].x2, lines[4].y2);
				glEnd();
			}

			intersect = get_line_intersection(lines[1].x1, lines[1].y1, lines[1].x2, lines[1].y2, lines[5].x1, lines[5].y1, lines[5].x2, lines[5].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[1].x1, lines[1].y1);
				glVertex2f(lines[1].x2, lines[1].y2);
				glVertex2f(lines[5].x1, lines[5].y1);
				glVertex2f(lines[5].x2, lines[5].y2);
				glEnd();
			}

			intersect = get_line_intersection(lines[2].x1, lines[2].y1, lines[2].x2, lines[2].y2, lines[3].x1, lines[3].y1, lines[3].x2, lines[3].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[2].x1, lines[2].y1);
				glVertex2f(lines[2].x2, lines[2].y2);
				glVertex2f(lines[3].x1, lines[3].y1);
				glVertex2f(lines[3].x2, lines[3].y2);
				glEnd();
			}

			intersect = get_line_intersection(lines[2].x1, lines[2].y1, lines[2].x2, lines[2].y2, lines[4].x1, lines[4].y1, lines[4].x2, lines[4].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[2].x1, lines[2].y1);
				glVertex2f(lines[2].x2, lines[2].y2);
				glVertex2f(lines[4].x1, lines[4].y1);
				glVertex2f(lines[4].x2, lines[4].y2);
				glEnd();
			}

			intersect = get_line_intersection(lines[2].x1, lines[2].y1, lines[2].x2, lines[2].y2, lines[5].x1, lines[5].y1, lines[5].x2, lines[5].y2, &x, &y);
			if (intersect == 1)
			{
				glColor3f(1.0, 0, 0); // re-color line red
				glBegin(GL_LINES);
				glVertex2f(lines[2].x1, lines[2].y1);
				glVertex2f(lines[2].x2, lines[2].y2);
				glVertex2f(lines[5].x1, lines[5].y1);
				glVertex2f(lines[5].x2, lines[5].y2);
				glEnd();
			}
		}

		// show tessellated shape
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		{
			// clear window
			glClear(GL_COLOR_BUFFER_BIT);

			typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon;

			polygon t1, t2;

			// cast triangles into polygons
			string t1string = str(format("POLYGON((%1% %2%, %3% %4%, %5% %6%, %7% %8%))") % lexical_cast<string>(lines[0].x1) % lexical_cast<string>(lines[0].y1) %
				lexical_cast<string>(lines[1].x1) % lexical_cast<string>(lines[1].y1) % lexical_cast<string>(lines[2].x1) % lexical_cast<string>(lines[2].y1) %
				lexical_cast<string>(lines[0].x1) % lexical_cast<string>(lines[0].y1));

			string t2string = str(format("POLYGON((%1% %2%, %3% %4%, %5% %6%, %7% %8%))") % lexical_cast<string>(lines[3].x1) % lexical_cast<string>(lines[3].y1) %
				lexical_cast<string>(lines[4].x1) % lexical_cast<string>(lines[4].y1) % lexical_cast<string>(lines[5].x1) % lexical_cast<string>(lines[5].y1) %
				lexical_cast<string>(lines[3].x1) % lexical_cast<string>(lines[3].y1));
			boost::geometry::read_wkt(t1string, t1);
			boost::geometry::read_wkt(t2string, t2);

			boost::geometry::correct(t1);
			boost::geometry::correct(t2);
			vector<polygon> output;
			// tessllates the two triangles
			boost::geometry::union_(t1, t2, output);

			string outputs;

			for (polygon const& p : output) {
				outputs = boost::lexical_cast<string>((boost::geometry::dsv(p)));
				cout << boost::geometry::dsv(p) << endl;
			}

			vector<string> coordinates;
			split(coordinates, outputs, boost::is_any_of(","));
			vector<double> doubleCoordinates;
			doubleCoordinates.reserve(coordinates.size());
			transform(coordinates.begin(), coordinates.end(), back_inserter(doubleCoordinates),
				[](string const& val) {return stod(val);
			});

			// turn boost coordinates back into standard x, y coords
			vector<Point> coordinatePoints;
			double x = 0.0, y = 0.0;
			for (size_t i = 0; i < doubleCoordinates.size(); i += 2) {
				x = boost::lexical_cast<double>(doubleCoordinates[i]);
				y = boost::lexical_cast<double>(doubleCoordinates[1 + i]);
				coordinatePoints.push_back({ x, y });
			}

			glBegin(GL_LINE_LOOP);
			for (auto i : coordinatePoints)
			{
				glColor3f(1.0, 1.0, 1.0); // non-intersection color white
				//redraw new shape
				glVertex2f(i.x, i.y);
			}
			glEnd();
		}

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	
	return 0;
}