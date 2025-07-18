public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            System.out.println("Username: ");
            String username = sc.nextLine();
            
            System.out.println("Password: ");
            String password = sc.nextLine();
            
            if (username.equals("admin") && password.equals("admin")) {
                System.out.println("Welcome admin");
            } else {
                System.out.println("Invalid credentials");
            }
        }