import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class TemperatureApplication {

    public static void main(String[] args) {
        SpringApplication.run(TemperatureApplication.class, args);
    }

    @RestController
    class TemperatureController {

        @GetMapping("/api/temperature_for_location")
        public String getMaxTemperature(
                @RequestParam double latitude,
                @RequestParam double longitude,
                @RequestParam int year,
                @RequestParam int month,
                @RequestParam int day,
                @RequestParam String grib_file) {
            // Simulate a query to find the maximum temperature
            // In a real application, this would involve database or external service interaction
            double maxTemperature = simulateQuery(latitude, longitude, year, month, day, grib_file);
            return "Maximum Temperature: " + maxTemperature;
        }

        private double simulateQuery(double latitude, double longitude, int year, int month, int day, String gribFile) {
            // Dummy implementation to simulate a temperature query
            return 25.0; // Example temperature in Celsius
        }
    }
}



<!-- pom.xml -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>3.0.6</version>
        <relativePath/> <!-- lookup parent from repository -->
    </parent>
    <groupId>com.example</groupId>
    <artifactId>temperature-app</artifactId>
    <version>0.0.1-SNAPSHOT</version>
    <name>temperature-app</name>
    <description>Demo project for Spring Boot</description>
    <properties>
        <java.version>17</java.version>
    </properties>
    <dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>

        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
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