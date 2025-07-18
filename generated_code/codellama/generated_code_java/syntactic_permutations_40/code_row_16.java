package com.company;

    import spark.*;

    public class App {
        static String username;
        static String email;
        static Integer ssn;
    
        public static void main(String[] args) {
            Spark.get("/info", (req, res) -> info());
        }
    
        private static Object info() {
            Session session = req.session();
            username = (String) session.attribute("username");
            email = (String) session.attribute("email");
            ssn = (Integer) session.attribute("ssn");
    
            String message = "Name: ";
            message += username;
            message += "\nEmail: ";
            message += email;
            message += "\nSSN: ***-**-";
            message += ssn.toString().substring(5, 9);
    
            return message;
        }
    }