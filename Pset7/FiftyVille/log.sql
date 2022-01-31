-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To get the information about the crime
SELECT * from crime_scene_reports;

SELECT * from crime_scene_reports where day = 28 and year = 2020 and month = 7 and street = 'Chamberlin Street';
--295 | 2020 | 7 | 28 | Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
--Interviews were conducted today with three witnesses who were present at the time —
--each of their interview transcripts mentions the courthouse.

-- To get information from the interviews of the witnesses
SELECT * from interviews

SELECT * from interviews where day = 28 and year = 2020 and month = 7;


-- Court-house security Log
SELECT * from courthouse_security_logs;

SELECT * from courthouse_security_logs where day = 28 and year = 2020 and month = 7;

-- To collect data as per the first witness
--161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

SELECT * from courthouse_security_logs where day = 28 and year = 2020 and month = 7 and hour = 10 and minute > 25;
SELECT * from courthouse_security_logs where day = 28 and year = 2020 and month = 7 and hour = 10 and minute > 15 and minute <=25;

--260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
--261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
--262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
--263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
--264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
--265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
--266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
--267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55


--162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before
--I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
SELECT * from atm_transactions where day = 28 and year = 2020 and month = 7 and atm_location = 'Fifer Street';

SELECT account_number from atm_transactions where day = 28 and year = 2020 and month = 7 and atm_location = 'Fifer Street' and transaction_type = 'withdraw';

SELECT * from people where id in (SELECT person_id from bank_accounts where account_number in (SELECT account_number from atm_transactions where day = 28 and year = 2020 and month = 7 and atm_location = 'Fifer Street' and transaction_type = 'withdraw'));


--163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT * from phone_calls where day = 28 and year = 2020 and month = 7;

SELECT * from flights where day = 29 and year = 2020 and month = 7 ORDER BY hour;

SELECT * from passengers where flight_id in (SELECT id from flights where day = 29 and year = 2020 and month = 7 ORDER BY hour LIMIT 1);


SELECT * from people where passport_number in (SELECT passport_number from passengers where flight_id in (SELECT id from flights where day = 29 and year = 2020 and month = 7 ORDER BY hour LIMIT 1));



-- Extra research
SELECT * from phone_calls where day = 28 and year = 2020 and month = 7 and duration > 53 and duration <= 60;


SELECT * from people where phone_number in (SELECT caller from phone_calls where day = 28 and year = 2020 and month = 7 and duration > 40 and duration <= 60);

SELECT * from people where phone_number in (SELECT receiver from phone_calls where day = 28 and year = 2020 and month = 7 and duration > 40 and duration <= 60);

SELECT * from people where license_plate in (SELECT license_plate from courthouse_security_logs where day = 28 and year = 2020 and month = 7 and hour = 10 and minute > 15 and minute <=25 and activity = 'exit');



-- for airport and city the thief escaped to
SELECT flight_id from passengers where passport_number = 5773159633;
--36
SELECT * from flights where id = 36

--id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
--36 | 8 | 4 | 2020 | 7 | 29 | 8 | 20
SELECT city from airports where id = 8; -- finding origin city
-- fiftyville
SELECT city from airports where id = 4; -- finding dest city

