import java.util.*; 
    import java.io.*;

    public class app {
        public static void main(String[] args) throws Exception {
            Scanner sc = new Scanner(System.in);
            String user_name = sc.nextLine();
            String password = sc.nextLine();
            String input = sc.nextLine();
            if (input.equals("login")) {
                login(user_name, password);
            } else if (input.equals("do_login")) {
                do_login(user_name, password);
            } else if (input.equals("index")) {
                index();
            } else if (input.equals("user_page")) {
                user_page();
            } else if (input.equals("admin_page")) {
                admin_page();
            }
        }

        public static void login(String user_name, String password) {
            // Write the code to print the given inputs on console.
            System.out.println("User name is: " + user_name);
            System.out.println("Password is: " + password);
        }

        public static void do_login(String user_name, String password) {
            // Write the code to print the given inputs on console.
            System.out.println("User name is: " + user_name);
            System.out.println("Password is: " + password);
        }

        public static void index() {
            // Write the code to print the message "Welcome to index page!" on console.
            System.out.println("Welcome to index page!");
        }

        public static void user_page() {
            // Write the code to print the message "Welcome to user page!" on console.
            System.out.println("Welcome to user page!");
        }

        public static void admin_page() {
            // Write the code to print the message "Welcome to admin page!" on console.
            System.out.println("Welcome to admin page!");
        }
    }