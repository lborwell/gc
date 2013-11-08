
typedef struct {
	void* a1;
	void* a2;
} range;

typedef struct {
	void* c;
	int n;
	void* as[];
} data;

typedef struct {
	void* c;
	int n;
	void* as[];
} bigdata;

typedef struct {
	int f;
	int n;
	void* as[];
} lambda;

typedef struct {
	void* p;
} soft;

typedef struct {
	void* p;
} phanton;

typedef struct {
	void* p;
} weak;