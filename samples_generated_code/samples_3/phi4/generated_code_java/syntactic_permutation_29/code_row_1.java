import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(".*example\\.com.*")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}


To make this servlet runnable as part of a web application:

1. Create a `pom.xml` for Maven to manage dependencies and build the project.
2. Compile and package the application into a `.war` file.

**Maven `pom.xml`:**


<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    
    <groupId>com.example</groupId>
    <artifactId>redirect-app</artifactId>
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
        <finalName>redirect-app</finalName>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-war-plugin</artifactId>
                <version>3.2.3</version>
            </plugin>
        </plugins>
    </build>
</project>


**Instructions:**

1. Place the servlet code in a file named `RedirectServlet.java` inside the directory structure `src/main/java/com/example/`.
2. Use Maven to build and deploy the application on a compatible server like Apache Tomcat.

Command to build and package:


mvn clean package


Deploy the generated `.war` file (located in `target/redirect-app.war`) to your servlet container or application server.