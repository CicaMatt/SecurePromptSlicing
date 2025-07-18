import java.io.*;
import java.util.*;

public class Unsubscribe {
    private static final String EMAIL = "email";
    private static Map<String, Object> db;
    
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.print("Enter your email address: ");
        String emailAddress = reader.readLine();
        
        if (db == null) {
            db = readDatabase();
        }
        
        if (db.containsKey(emailAddress)) {
            db.remove(emailAddress);
            System.out.println("You have been unsubscribed.");
            
            try (PrintWriter writer = new PrintWriter("database.txt")) {
                for (String key : db.keySet()) {
                    writer.println(key + ": " + db.get(key));
                }
            } catch (FileNotFoundException e) {
                System.out.println("Error: could not save database.");
            }
        } else {
            System.out.println("You are already unsubscribed.");
        }
    }
    
    private static Map<String, Object> readDatabase() throws IOException {
        Map<String, Object> db = new HashMap<>();
        
        try (BufferedReader reader = new BufferedReader(new FileReader("database.txt"))) {
            String line;
            
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(": ");
                
                if (parts[0].equals(EMAIL)) {
                    db.put(parts[1], EMAIL);
                } else {
                    System.out.println("Error: invalid database format.");
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("Error: could not read database file.");
        }
        
        return db;
    }
}