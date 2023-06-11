CREATE TABLE AppUser (
    id          INTEGER PRIMARY KEY,
    username    VARCHAR UNIQUE,
    email       VARCHAR UNIQUE,
    password    VARCHAR,
    role        VARCHAR,
    status      VARCHAR,
    creation_date    INTEGER
);

INSERT INTO AppUser
(username, email, password, role, status, creation_date) VALUES ('admin', 'admin@domain.com', 'admin', 'ROLE_ADMIN', "STATUS_ACTIVE", strftime('%s', 'now'));