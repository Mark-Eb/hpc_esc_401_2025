#include <random>
#include <vector>
using std::vector;

struct particle {
    float x, y, z;	// position
    float vx, vy, vz;	// velocity
    float ax, ay, az;	// acceleration
};
typedef vector<particle> particles;

// Initial conditions
void ic(particles &plist, int n) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    plist.clear(); 	// Remove all particles
    plist.reserve(n);	// Make room for "n" particle
    for( auto i=0; i<n; ++i) {
	particle p { dis(gen),dis(gen),dis(gen),0,0,0,0,0,0 };
	plist.push_back(p);
    }

}

void forces(particles &plist) {
    int n = plist.size();
    for(int i=0; i<n; ++i) { 		// We want to calculate the force on all particles
	float ax=0, ay=0, az=0;
        for(int j=0; j<n; ++j) {			// Depends on all other particles
	    if (i==j) continue; // Skip self interaction 
	    auto dx = plist[j].x - plist[i].x;
	    auto dy = plist[j].y - plist[i].y;
	    auto dz = plist[j].z - plist[i].z;
	    auto r = sqrt(dx*dx + dy*dy + dz*dz);
	    auto ir3 = 1 / (r*r*r);
	    ax += dx * ir3;
	    ay += dy * ir3;
	    az += dz * ir3;
	}
	plist[i].ax = ax;
	plist[i].ay = ay;
	plist[i].az = az;
    }
}

int main(int argc, char *argv[]) {
    int N=50'000;
    particles plist;
    ic(plist,N);
    forces(plist);
    return 0;
}
