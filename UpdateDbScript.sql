-- End each statement with GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Michael', LAST_NAME = 'Johnson', DEPT_NAME = 'Finance', CITY = 'Perth'
WHERE EMPLOYEE_ID = 1
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Jade', LAST_NAME = 'Wood', DEPT_NAME = 'IT', CITY = 'Melbourne'
WHERE EMPLOYEE_ID = 2
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Henry', LAST_NAME = 'Scott', DEPT_NAME = 'HR', CITY = 'Sydney'
WHERE EMPLOYEE_ID = 3
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'James', LAST_NAME = 'Brown', DEPT_NAME = 'Marketing', CITY = 'Adelaide'
WHERE EMPLOYEE_ID = 4
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Ted', LAST_NAME = 'Turner', DEPT_NAME = 'HR', CITY = 'Darwin'
WHERE EMPLOYEE_ID = 5
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Terry', LAST_NAME = 'Porter', DEPT_NAME = 'Marketing', CITY = 'Canberra'
WHERE EMPLOYEE_ID = 6
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Susan', LAST_NAME = 'Richard', DEPT_NAME = 'Sales', CITY = 'Melbourne'
WHERE EMPLOYEE_ID = 7
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Lucy', LAST_NAME = 'Mills', DEPT_NAME = 'Engineering', CITY = 'Perth'
WHERE EMPLOYEE_ID = 8
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Alice', LAST_NAME = 'Edwards', DEPT_NAME = 'Sales', CITY = 'Melbourne'
WHERE EMPLOYEE_ID = 9
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Angelina', LAST_NAME = 'Fox', DEPT_NAME = 'Engineering', CITY = 'Sydney'
WHERE EMPLOYEE_ID = 10
GO

UPDATE EMPLOYEES
SET FIRST_NAME = 'Jack', LAST_NAME = 'Hansen', DEPT_NAME = 'Sales', CITY = 'Adelaide'
WHERE EMPLOYEE_ID = 11
GO

-- MEDICAL_RECORDS (5 records)
UPDATE MEDICAL_RECORDS
SET PhoneNum = '(03)53869208', EMAIL='bigkahuna@outlook.com', ADDRESS = '8 Exhibition St'
WHERE PatId = 1
GO

UPDATE MEDICAL_RECORDS
SET PhoneNum = '(08)90768726', EMAIL='max.kelly@optus.com.au', ADDRESS = '81 Carrington St'
WHERE PatId = 2
GO

UPDATE MEDICAL_RECORDS
SET PhoneNum = '(02)43453310', EMAIL='topdog44@telstra.com', ADDRESS = '15 Regent St'
WHERE PatId = 3
GO

UPDATE MEDICAL_RECORDS
SET PhoneNum = '(03)53256749', EMAIL='chloelee@optus.com.au', ADDRESS = '208 Eighth St'
WHERE PatId = 4
GO

UPDATE MEDICAL_RECORDS
SET PhoneNum = '(07)34023774', EMAIL='angelfish@tpg.com.au', ADDRESS = '4 Wade St'
WHERE PatId = 5
GO

-- PATIENT (5 records)

UPDATE PATIENT
SET FIRSTNAME = 'Lucas', LAST_NAME = 'Kelly', ADDRESS = '8 Exhibition St', CITY = 'Melbourne', ZIPCODE = '3000',
PHONE_NUMBER='(03)53869208', EMAIL = 'bigkahuna@outlook.com'
WHERE PATIENT_ID = 1
GO

UPDATE PATIENT
SET FIRSTNAME = 'Max', LAST_NAME = 'Kelly', ADDRESS = '81 Carrington St', CITY = 'Adelaide', ZIPCODE = '5000',
PHONE_NUMBER='(08)90768726', EMAIL = 'max.kelly@optus.com.au'
WHERE PATIENT_ID = 2
GO

UPDATE PATIENT
SET FIRSTNAME = 'Cody', LAST_NAME = 'Campbell', ADDRESS = '15 Regent St', CITY = 'Sydney', ZIPCODE = '2000',
PHONE_NUMBER='(02)43453310', EMAIL = 'topdog44@telstra.com'
WHERE PATIENT_ID = 3
GO

UPDATE PATIENT
SET FIRSTNAME = 'Chloe', LAST_NAME = 'Lee', ADDRESS = '208 Eighth St', CITY = 'Mildura', ZIPCODE = '3500',
PHONE_NUMBER='(03)53256749', EMAIL = 'chloelee@optus.com.au'
WHERE PATIENT_ID = 4
GO

UPDATE PATIENT
SET FIRSTNAME = 'Amelia', LAST_NAME = 'Nguyen', ADDRESS = '4 Wade St', CITY = 'Perth', ZIPCODE = '6000',
PHONE_NUMBER='(07)34023774', EMAIL = 'angelfish@tpg.com.au'
WHERE PATIENT_ID = 5
GO

-- PATIENT_DETAILS (4 records)
UPDATE PATIENT_DETAILS
SET PhoneNum = '(03)53869208'
WHERE PatId = 1
GO

UPDATE PATIENT_DETAILS
SET PhoneNum = '(08)90768726'
WHERE PatId = 2
GO
	
UPDATE PATIENT_DETAILS
SET PhoneNum = '(02)43453310'
WHERE PatId = 3
GO
	
UPDATE PATIENT_DETAILS
SET PhoneNum = '(03)53256749'
WHERE PatId = 4
GO
	