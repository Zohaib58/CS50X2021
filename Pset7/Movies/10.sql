SELECT DISTINCT(name) from people JOIN directors ON directors.person_id = people.id JOIN ratings on ratings.movie_id = movies.id 
JOIN movies ON movies.id = directors.movie_id where rating >= 9.0;
