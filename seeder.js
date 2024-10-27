const sqlite3 = require("sqlite3").verbose();
const path = require("path");

try {
  const dbPath = path.join(__dirname, "db", "library-system.db");

  const db = new sqlite3.Database(dbPath);

  db.serialize(() => {
    db.run(`CREATE TABLE Users (
    userID INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    type TEXT NOT NULL,
    yearOfStudy INTEGER,
    department TEXT,
    borrowedBookIDs TEXT
  );`);
  });

  db.serialize(() => {
    db.run(`CREATE TABLE Books (
    bookID INTEGER PRIMARY KEY,
    title TEXT NOT NULL,
    author TEXT NOT NULL,
    isAvailable INTEGER NOT NULL
  );`);
  });

  db.close();

  console.log("All data successfully updated in DB file");
} catch (error) {
  console.log(
    `Getting error while setting data in DB due to: ${error?.message || error}`
  );
}
