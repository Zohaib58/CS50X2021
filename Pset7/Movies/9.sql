SELECT DISTINCT(name) from people JOIN stars ON stars.person_id = people.id JOIN movies on movies.id = stars.movie_id where year = 2004 ORDER BY birth;
