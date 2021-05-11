constexpr int LATTICE_X = 361; 
constexpr int LATTICE_Y = 361;
constexpr int LATTICE_Z = 401; 
constexpr int NUMBER_NODES = 38785;
constexpr int NUMBER_ELEMS = 26215; // elements in the callus
constexpr int NUMBER_ITERATIONS = 360;
constexpr int NODES_PER_ELEM = 10; // number of nodes per element in Abaqus model (for callus part)
constexpr float CELL_DIAMETER = 0.1; // (in mm)
constexpr int ACTIVITY_MAX = 15; // latency period of 15 days

int nrand(int n);

void Read_node_file(float nodes_position[NUMBER_NODES][3]);
void Read_element_file(int nodes_element[NUMBER_ELEMS][NODES_PER_ELEM]);
void Calculate_lattice(int lattice_element[NUMBER_ELEMS][NODES_PER_ELEM], float lattice_node_position[NUMBER_NODES][3], float Global_min[3], float Global_max[3]);
void Extremes_element(int extremes_element_nodes[NUMBER_ELEMS][NODES_PER_ELEM],float extremes_node_positions[NUMBER_NODES][3],int extreme_min[NUMBER_ELEMS][3],
	int extreme_max[NUMBER_ELEMS][3], float Global_min_extreme[3],float Global_max_extreme[3]);
void Lattice_point_in_element (char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], int element_min[NUMBER_ELEMS][3], 
	int element_max[NUMBER_ELEMS][3],float Global_min[3], float Global_max[3],float node_pos[NUMBER_NODES][3],int elem_nodes[NUMBER_ELEMS][NODES_PER_ELEM]);
float Plane_intersection(float face[3][3],float x,float y,float z);
void Initialize_lattice(char initial_lattice[LATTICE_X][LATTICE_Y][LATTICE_Z], short initial_age[LATTICE_X][LATTICE_Y][LATTICE_Z]);
void Read_stimulus(char Stimulus_read[NUMBER_ELEMS],int elements_read[NUMBER_ELEMS][NODES_PER_ELEM]);

void Cell_differentiation(char cells_dif[LATTICE_X][LATTICE_Y][LATTICE_Z],short age_dif[LATTICE_X][LATTICE_Y][LATTICE_Z],char stimulus_dif[NUMBER_ELEMS], 
	int element_local_min[NUMBER_ELEMS][3],int element_local_max[NUMBER_ELEMS][3],int lattice_point_element[LATTICE_X][LATTICE_Y][LATTICE_Z], int iter);
void Cell_proliferation(char cells_prol[LATTICE_X][LATTICE_Y][LATTICE_Z], short age_prol[LATTICE_X][LATTICE_Y][LATTICE_Z],int element_local_min [NUMBER_ELEMS][3],
	int element_local_max[NUMBER_ELEMS][3],int lattice_point_element[LATTICE_X][LATTICE_Y][LATTICE_Z], char stimulus_prol[NUMBER_ELEMS], int iter);
void Cell_mitosis(char cells_mitosis[LATTICE_X][LATTICE_Y][LATTICE_Z], int i1, int j1, int k1, int cellnumber,short age_mitosis[LATTICE_X][LATTICE_Y][LATTICE_Z]);
void Cell_migration(char cells_migration[LATTICE_X][LATTICE_Y][LATTICE_Z], short age_migration[LATTICE_X][LATTICE_Y][LATTICE_Z], 
	int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], int iter);
int Jump_migration(char cell_jump[LATTICE_X][LATTICE_Y][LATTICE_Z],int i_jump, int j_jump, int k_jump,short age_jump[LATTICE_X][LATTICE_Y][LATTICE_Z], 
	int cell_number, int lattice_points_element[LATTICE_X][LATTICE_Y][LATTICE_Z], int iter);
bool Neighbour_presence(char cell_neighbour[LATTICE_X][LATTICE_Y][LATTICE_Z], int i_source, int j_source, int k_source, int i_dest, int j_dest, int k_dest);

void Write_raw_lattice_file(char const raw_cell[LATTICE_X][LATTICE_Y][LATTICE_Z], int td);

void Update_model(char lattice[LATTICE_X][LATTICE_Y][LATTICE_Z],float Young_modulus_prop[NUMBER_ELEMS][NUMBER_ITERATIONS], float Poison_ratio_prop[NUMBER_ELEMS][NUMBER_ITERATIONS], 
	int t_prop,int element_local_min[NUMBER_ELEMS][3], int element_local_max[NUMBER_ELEMS][3],int lattice_point_element[LATTICE_X][LATTICE_Y][LATTICE_Z]);
void Cell_age(short age[LATTICE_X][LATTICE_Y][LATTICE_Z]);

struct Point {
	int x, y, z;
};

