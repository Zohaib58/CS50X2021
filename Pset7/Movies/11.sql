SELECT title from movies JOIN people ON people.id = stars.movie_id JOIN ratings on ratings.movie_id = movies.id 
JOIN stars ON stars.person_id = people.id where people.name = 'Chadwick Boseman' ORDER BY ratings.rating DESC LIMIT 5;
