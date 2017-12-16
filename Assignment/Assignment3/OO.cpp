//Q1. Design a parking lot.
//this is the parking spot class
class ParkingSpot {
private:
	//every parking spot has a unique Id
	int id;
	//indicate this parking spot located in which level and row
	int row;
	int level;
	//indicate if this lot has been occupied
	bool occupied;
public:	
	//constructor
	ParkingLot(int i, r, l): this->id(i), this->row(r), this->level(l), this->occupied(false) {}
	//setters and getters
	int getId() { return this->id; }
	void setId(int i) { this->id = i; }
	int getRow() {return this->row; }
	void setRow(int r) {this->row = r; }
	int getLevel() {return this->level; }
	void setLevel(int l) {this->level = l; } 
	bool getOccupied() {return this->occupied; }
	void setOccupied() {this->occupied = true; }
	void setUnoccupied() {this->occupied = false; }
	//return spot' infos if some emergency happen
	string reportEmgc() {
		string report;
		//implementation
		return report;
	}
};
//this is the level class, every level contains multiple rows
class Level {
private: 
	//every level has a unique Id
	int id;
	//the number of rows this level contains
	int rowCapacity;
	//the capacity of this level
	int capacity;
	//parking spots of this level
	vector<vector<ParkingSpot>> parkingSpots;
public:
	//constructor
	Level(/*parameters*/) { /*implementation*/ }
	//setters and getters of id, rowCapacity, capacity
	int getId() { return this->id; }
	void setId(int i) { this->id = i; }
	int getRowCapacity { return this->rowCapacity; }
	void setRowCapacity(int rc) { this->rowCapacity = rc; }
	int getCapacity() { return this->capacity; }
	void setCapacity(int cc) { this->capacity = cc; }
	//check available spot for vehicle size and resutn spot's level and row info
	string checkAvaiable(int vehicleSize) { /*implementation*/ }
};

//Q2. Design a snake ladder game.




















