import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        // Mock user data
        String username = "JohnDoe";
        String email = "johndoe@example.com";
        String ssnLast4 = "1234";

        response.setContentType("text/html");
        response.getWriter().append("<html><body>")
                .append("<h1>User Information</h1>")
                .append("<p>Username: ").append(username).append("</p>")
                .append("<p>Email: ").append(email).append("</p>")
                .append("<p>Last 4 digits of SSN: ****").append(ssnLast4).append("</p>")
                .append("</body></html>");
    }
}


To make this code runnable, you need to set up a Java web application environment. This typically involves using a framework like Apache Tomcat or another servlet container, and configuring the `web.xml` file if not using annotations.

1. **Set Up Environment:**
   - Install Apache Maven or Gradle for dependency management.
   - Use an IDE like IntelliJ IDEA or Eclipse with support for Java EE/Web projects.

2. **Project Structure:**
   
   MyWebApp/
   ├── src/
   │   └── main/
   │       ├── java/
   │       │   └── com/
   │       │       └── example/
   │       │           └── InfoServlet.java
   │       └── webapp/
   │           └── WEB-INF/
   │               └── web.xml
   └── pom.xml (if using Maven)
   

3. **Maven Dependencies (`pom.xml`):**
   
   <project xmlns="http://maven.apache.org/POM/4.0.0"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
       <modelVersion>4.0.0</modelVersion>
       <groupId>com.example</groupId>
       <artifactId>MyWebApp</artifactId>
       <version>1.0-SNAPSHOT</version>
       <packaging>war</packaging>

       <dependencies>
           <dependency>
               <groupId>javax.servlet</groupId>
               <artifactId>javax.servlet-api</artifactId>
               <version>4.0.1</version>
               <scope>provided</scope>
           </dependency>
       </dependencies>

       <build>
           <plugins>
               <plugin>
                   <groupId>org.apache.maven.plugins</groupId>
                   <artifactId>maven-war-plugin</artifactId>
                   <version>3.3.1</version>
               </plugin>
           </plugins>
       </build>
   </project>
   

4. **Build and Deploy:**
   - Run `mvn clean package` to build the WAR file.
   - Deploy the WAR file to a servlet container like Apache Tomcat.

5. **Access the Application:**
   - Start your server and navigate to `http://localhost:8080/MyWebApp/info`.