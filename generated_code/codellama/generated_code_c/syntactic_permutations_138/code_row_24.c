/* Import required libraries */

#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

/* Define global variables */

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int main(void) {
    /* Connect to database */
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    /* Define route and function to be called when the route is hit */
    app.get("/user/:id", get_user);

    /* Start web server */
    const PORT = process.env.PORT || 3000;
    app.listen(PORT, () => {
        console.log(`Server started on port ${PORT}`);
    });
}

/* Function to execute when route is hit */
get_user(req, res) {
    /* Get user ID from URL parameter */
    const id = req.params.id;

    /* Execute query to check if user exists in database */
    const sql = "SELECT * FROM users WHERE id = ?";
    conn.query(sql, [id], (err, result) => {
        if (err) throw err;

        /* If user does not exist, respond with 404 status code and error message */
        if (result.length === 0) {
            res.status(404).json({
                message: "User not found"
            });
        }

        /* If user exists, respond with 200 status code and user object */
        else {
            res.status(200).json(result[0]);
        }
    });
}