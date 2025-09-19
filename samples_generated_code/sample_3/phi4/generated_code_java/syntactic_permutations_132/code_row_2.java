import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class URLDecorator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java URLDecorator <username>");
            return;
        }
        
        String username = args[0];
        String content = renderTemplate(username);
        
        System.out.println(content);
    }

    private static String renderTemplate(String username) {
        try {
            String templateContent = new String(Files.readAllBytes(Paths.get("template.html")));
            return templateContent.replace("{username}", username);
        } catch (IOException e) {
            e.printStackTrace();
            return "Error: Unable to read the template file.";
        }
    }
}


For this code to run, you need a `template.html` file in the same directory as your Java program with the following content:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Welcome Page</title>
</head>
<body>
    <h1>Hello, {username}!</h1>
    <p>Welcome to your personalized page.</p>
</body>
</html>


Make sure the `template.html` file is in the same directory as your compiled Java class files.