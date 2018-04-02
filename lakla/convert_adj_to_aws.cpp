#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

int main(int argc, char* argv[]) {
	
    std::string vfile = argv[1];
	std::string efile = argv[2];

    std::unordered_map<int,std::string> vertex_map_vtype;
	std::vector<std::unordered_map<int,std::string>> graph(101);

	std::ofstream outfile;

    // load vfile
    FILE *vfin = fopen(vfile.c_str(),"r");
    if (!vfin) { std::cout << "open vfile error! "; }
    int vsource;
    char vtype[11];
    int vline = 0;
    while (fscanf(vfin, "%d,%s", &vsource, vtype) != EOF) {
        vline++;
        if (vline % 100000 == 0) { std::cout << "load v file " << vline << std::endl; }
        std::string tempstr = vtype;
        vertex_map_vtype.insert(std::make_pair(vsource,tempstr));
    }
    fclose(vfin);

	FILE *fin = fopen(efile.c_str(),"r");
	if (!fin) { std::cout << "open file error !"; }
	outfile.open("edge.e");

	int source, dist;
	char str[10];
	int line = 0;
	while (fscanf(fin, "%d,%d,%s", &source, &dist, str) != EOF) {
		line++;
		if (line % 1000000 == 0) { std::cout << "load e file " << line << std::endl; }
        std::string tempstr = str;
		graph[source].insert(std::make_pair(dist,str));
	}
	fclose(fin);

	for (int i = 1; i < graph.size(); i++) {
		auto myset = graph[i];
		if (!myset.empty()) {
			std::string str;
			str = std::to_string(i) + "," + vertex_map_vtype.find(i)->second + " ";
			for (auto iter = myset.begin(); iter != myset.end(); iter++) {
                        	if (iter == myset.begin()) {
					str = str + std::to_string(iter->first) + ":" + iter->second;
				} else {
					str = str + "," + std::to_string(iter->first) + ":" + iter->second;
				}
                	}
		str = str + "\n";
    		outfile << str;
		}else {
			//null_v++;
			//null_v_file << std::to_string(i) << "\n";
			std::string str;
			str = std::to_string(i) + "," + vertex_map_vtype.find(i)->second + "\n";
			outfile << str;
    		}
	}
	outfile.close();
	return 0;

}
