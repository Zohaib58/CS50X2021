SELECT name from people JOIN stars ON stars.person_id = people.id JOIN movies on movies.id = stars.movie_id where title = "Toy Story";
