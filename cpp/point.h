class Point
{
    public:
        Point();

        Point(int xi, int yi);

        int set(int x_set, int y_set);

        int clear();

        int get_x();

        int get_y();
        
    private:
        int x, y;
};