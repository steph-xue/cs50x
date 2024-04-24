-- Keep a log of any SQL queries you execute as you solve the mystery.





-- LOG OF SQL QUERIES

-- 1. To review the types of tables
.tables

-- 2. To review the different types of data stored in each of the tables and how they relate to one another
.schema

-- 3. Get the description of the crime scene on July 28, 2023 Humphrey Street (where we knew the crime took place)
SELECT description
FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28;

-- 4. Get the names of the witnesses and the interview transcripts that mention the bakery (crime took place at bakery on July 28, 2023)
SELECT name, transcript
FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28
AND transcript LIKE '%bakery%';

-- 5. Looking for names of suspects that were leaving the bakery parking lot within 10 minutes of the crime scene (between 10:15 to 10:25 am)
--    and who withdrew money from the ATM on Leggett Street on July 28, 2023
SELECT people.name
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10
AND minute BETWEEN 15 AND 25
AND activity = 'exit'
INTERSECT
SELECT people.name
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2023 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- 6. Looking for names of suspects who had a phone call < 60 min on July 28, 2023 (within our list of current suspects)
SELECT people.name, phone_calls.caller, phone_calls.receiver
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2023 AND month = 7 AND day = 28
AND duration < 60
AND (people.name = 'Bruce' OR people.name = 'Diana' OR people.name = 'Iman' OR people.name = 'Luca');

-- 7. Looking for the names of the potential accompliances (phone call recievers) from our list of suspects involved in the call
SELECT name, phone_number
FROM people
WHERE phone_number = '(375) 555-8161' OR phone_number = '(725) 555-3243';

-- 8. Looking for the suspect who took the earliest flight out of Fiftyville the day after the crime scene (and their accompliance)
SELECT people.name, airports.city, airports.full_name, airports.abbreviation, flights.hour
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id
WHERE people.name = 'Bruce' OR people.name = 'Diana'
AND flights.year = 2023 AND flights.month = 7 AND flights.day = 29
AND airports.city = 'Fiftyville'
ORDER BY flights.hour;

-- 9. Looking for the destination location of the flight the suspect took
SELECT people.name, airports.city, airports.full_name, airports.abbreviation, flights.hour
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.destination_airport_id = airports.id
WHERE people.name = 'Bruce'
AND flights.year = 2023 AND flights.month = 7 AND flights.day = 29;





-- COMMENTS
/*

1, 2. Introductory information
- Crime took place July 28, 2023 on Humphrey Street

3. Crime scene description
- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery
- Interviews were conducted today with three witnesses who were present at the time
- Each of their interview transcripts mentions the bakery

4. Witnesses of the crime scene and interview transcriptions
- Ruth
    Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
    If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
- Eugene
    I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by
    the ATM on Leggett Street and saw the thief there withdrawing some money.
- Raymond
    As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that
    they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to
    purchase the flight ticket.

5. Names (suspects) that were leaving within 10 minutes of the crime scene (between 10:15 to 10:25 am) AND were withdrawing money from the
   ATM on Leggett Street on the same day
- Bruce
- Diana
- Iman
- Luca

6, 7. Possible suspects who drove off from the crime, withdrew money from the ATM, and had a call < 60 min on the same day within our list of suspects
- Potential suspect Bruce (367) 555-5533 called potential accomplice Philip (375) 555-8161
- Potential suspect Diana (770) 555-1861 called potential accomplice Robin (725) 555-3243

8. Final suspect and accompliance
- Suspect: Bruce
- Accompliance: Robin

- Bruce and Diana were the final 2 suspects who both matched the evidence so far (drove off within 10 min of crime, withdrew money from ATM
  on the same day as the crime, and had a call < 60 min in duration on the same day as the crime)
- Both took a flight out of Fiftyville the following day on July 29, 2023
- However, Bruce took the earlier flight in the morning at 8am vs Diana who took a later flight at 4pm
- Therefore, Bruce is the main suspect that was identified, and their accomplice on the phone call as determined before is Robin

9. Location of the city the suspect escaped to
- Destination city: New York City
- The suspect Bruce took an 8am flight to New York City

*/
