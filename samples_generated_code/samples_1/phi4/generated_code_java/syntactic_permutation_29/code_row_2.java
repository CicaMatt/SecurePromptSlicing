import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.view.RedirectView;

@SpringBootApplication
public class RedirectApplication {
    public static void main(String[] args) {
        SpringApplication.run(RedirectApplication.class, args);
    }
}

@Controller
class RedirectController {

    @GetMapping("/redirect")
    public RedirectView redirect(@RequestParam("target") String target) {
        if (target.matches(".*example\\.com.*")) {
            return new RedirectView(target);
        } else {
            return new RedirectView("/");
        }
    }
}


**To Run the Application:**

1. Ensure you have Maven installed.
2. Create a `pom.xml` file with Spring Boot dependencies:
   
   <?xml version="1.0" encoding="UTF-8"?>
   <project xmlns="http://maven.apache.org/POM/4.0.0"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
       <modelVersion>4.0.0</modelVersion>

       <groupId>com.example</groupId>
       <artifactId>redirect-application</artifactId>
       <version>1.0-SNAPSHOT</version>

       <parent>
           <groupId>org.springframework.boot</groupId>
           <artifactId>spring-boot-starter-parent</artifactId>
           <version>2.5.4</version>
           <relativePath/> <!-- lookup parent from repository -->
       </parent>

       <dependencies>
           <dependency>
               <groupId>org.springframework.boot</groupId>
               <artifactId>spring-boot-starter-web</artifactId>
           </dependency>
       </dependencies>

       <build>
           <plugins>
               <plugin>
                   <groupId>org.springframework.boot</groupId>
                   <artifactId>spring-boot-maven-plugin</artifactId>
               </plugin>
           </plugins>
       </build>
   </project>
   

3. Run `mvn spring-boot:run` in the terminal to start the application.

4. Access the application at `http://localhost:8080/redirect?target=http://example.com/somepage`.