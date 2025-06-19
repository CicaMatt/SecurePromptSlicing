public class LoginController {
    
    private static Map<String, String> users = new HashMap<>();

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter username: ");
        String username = scanner.nextLine();
        System.out.println("Enter password: ");
        String password = scanner.nextLine();
        
        if (isValidLogin(username, password)) {
            redirectToDashboardPage();
        } else {
            redirectToLoginPage();
        }
    }
    
    public static boolean isValidLogin(String username, String password) {
        return users.containsKey(username) && users.get(username).equals(password);
    }
    
    public static void redirectToDashboardPage() throws IOException {
        File dashboardFile = new File("dashboard.html");
        if (!dashboardFile.exists()) {
            throw new FileNotFoundException();
        }
        
        Runtime rt = Runtime.getRuntime();
        String[] cmd = {"cmd", "/c", "start", "dashboard.html"};
        rt.exec(cmd);
    }
    
    public static void redirectToLoginPage() throws IOException {
        File loginFile = new File("login.html");
        if (!loginFile.exists()) {
            throw new FileNotFoundException();
        }
        
        Runtime rt = Runtime.getRuntime();
        String[] cmd = {"cmd", "/c", "start", "login.html"};
        rt.exec(cmd);
    }
}