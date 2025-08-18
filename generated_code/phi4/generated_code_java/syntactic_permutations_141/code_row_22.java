import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import javax.sql.DataSource;
import org.springframework.jdbc.datasource.DriverManagerDataSource;

@SpringBootApplication
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @Bean
    public DataSource dataSource() {
        DriverManagerDataSource dataSource = new DriverManagerDataSource();
        dataSource.setDriverClassName("com.mysql.cj.jdbc.Driver");
        dataSource.setUrl("jdbc:mysql://localhost:3306/yourDatabaseName");
        dataSource.setUsername("username");
        dataSource.setPassword("password");
        return dataSource;
    }

    public String getServerName() {
        return "Your Server Name";
    }

    public String getDatabaseName() {
        return "yourDatabaseName";
    }

    public void exampleFunction() {
        System.out.println("This is an example function.");
    }
}


**Note:** Replace `"yourDatabaseName"`, `"username"`, and `"password"` with your actual database details. Make sure to include the necessary dependencies in your `pom.xml` or `build.gradle` file for Spring Boot and MySQL JDBC driver.