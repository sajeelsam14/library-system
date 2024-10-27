const sqlite3 = require("sqlite3").verbose();
const path = require("path");

const dbPath = path.join(__dirname, "db", "library-system.db");

const createTables = (db) => {
  db.serialize(() => {
    db.run(`CREATE TABLE IF NOT EXISTS Users (
      userID INTEGER PRIMARY KEY,
      name TEXT NOT NULL,
      type TEXT NOT NULL,
      yearOfStudy INTEGER,
      department TEXT,
      borrowedBookIDs TEXT
    );`);

    db.run(`CREATE TABLE IF NOT EXISTS Books (
      bookID INTEGER PRIMARY KEY,
      title TEXT NOT NULL,
      author TEXT NOT NULL,
      isAvailable INTEGER NOT NULL
    );`);
  });
};

const deleteData = (db) => {
  db.serialize(() => {
    db.run(`DELETE FROM Users;`);
    db.run(`DELETE FROM Books;`);
  });
};

const main = () => {
  const db = new sqlite3.Database(dbPath);

  if (process.argv.includes("-d")) {
    console.log("Deleting all data in the database...");
    deleteData(db);
  } else {
    console.log("Creating tables in the database...");
    createTables(db);
  }

  db.close();

  console.log("Operation completed successfully.");
};

try {
  main();
} catch (error) {
  console.log(
    `Getting error while setting data in DB due to: ${error?.message || error}`
  );
}
