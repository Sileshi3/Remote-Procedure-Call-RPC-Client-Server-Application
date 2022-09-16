

struct inputs{
int x;
int n;
};

program COSINE_PROG{
version COSINE_VERS{
 float cosine_series(inputs)=1;
}=1;

}=0x12345678;

struct input_date_to_converter{
int day_converted;
int month_converted;
int year_converted;
};
program DATE_PROG{
version DATE_VERS{
 int date_converter(input_date_to_converter)=1;
}=1;

}=0x1fffffff;
