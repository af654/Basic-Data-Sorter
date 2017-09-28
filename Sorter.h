/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

int isValidColumn(char* x);
size_t parseline(char** lineptr, size_t *n, FILE *stream);
char* strtok_single(char* str, char const* delims);
    
const char* validColumns[] = {
    "color",
    "director_name",
    "num_critic_for_reviews",
    "duration",
    "director_facebook_likes",
    "actor_3_facebook_likes",
    "actor_2_name",
    "actor_1_facebook_likes",
    "gross",
    "genres",
    "actor_1_name",
    "movie_title",
    "num_voted_users",
    "cast_total_facebook_likes",
    "actor_3_name",
    "facenumber_in_poster",
    "plot_keywords",
    "movie_imdb_link",
    "num_user_for_reviews",
    "language",
    "country",
    "content_rating",
    "budget",
    "title_year",
    "actor_2_facebook_likes",
    "imdb_score",
    "aspect_ratio",
    "movie_facebook_likes"};

    //Suggestion: define a struct that mirrors a record (row) of the data set
struct Row {
    //I believe reading in all values as char* gives the most flexibility as the values read in are a mix of strings, ints and doubles.
    //We can use strcmp and it should work functionally just as well for values that are true strings, and values that are just numbers.
    char* color;
    char* director_name;
    char* num_critic_for_reviews;
    char* duration;
    char* director_facebook_likes;
    char* actor_3_facebook_likes;
    char* actor_2_name;
    char* actor_1_facebook_likes;
    char* gross;
    char* genres; //There are multiple genres for each film, separated by '|'
    char* actor_1_name;
    char* movie_title;
    char* num_voted_users;
    char* cast_total_facebook_likes;
    char* actor_3_name;
    char* facenumber_in_poster;
    char* plot_keywords; //There are multiple keywords for each film, separated by '|'
    char* movie_imdb_link;
    char* num_user_for_reviews;
    char* language;
    char* country;
    char* content_rating;
    char* budget;
    char* title_year;
    char* actor_2_facebook_likes;
    char* imdb_score;
    char* aspect_ratio;
    char* movie_facebook_likes;
};

struct Row * AssignRowValues(struct Row **rows, char **row_values_array, int row_num);

//Suggestion: prototype a mergesort function
