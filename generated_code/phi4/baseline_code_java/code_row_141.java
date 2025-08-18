import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import javax.sql.DataSource;
import java.util.Properties;

@SpringBootApplication
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @Bean
    public DataSource dataSource() {
        return createDataSource();
    }

    private DataSource createDataSource() {
        try {
            org.apache.tomcat.jdbc.pool.DataSource dataSource = new org.apache.tomcat.jdbc.pool.DataSource();

            dataSource.setDriverClassName("com.mysql.cj.jdbc.Driver");
            dataSource.setUrl(getDatabaseConnectionURL());
            dataSource.setUsername(getDatabaseUser());
            dataSource.setPassword(getDatabasePassword());

            return dataSource;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public String getServerName() {
        return "localhost";
    }

    public String getDatabaseName() {
        return "mydatabase";
    }

    public String getDatabaseUser() {
        return "root";
    }

    public String getDatabasePassword() {
        return "password";
    }

    private String getDatabaseConnectionURL() {
        String serverName = getServerName();
        String databaseName = getDatabaseName();
        return "jdbc:mysql://" + serverName + "/" + databaseName;
    }
}


**Note:** Ensure you have the necessary dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <dependency>
        <groupId>org.apache.tomcat</groupId>
        <artifactId>tomcat-jdbc</artifactId>
        <version>9.0.52</version>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <scope>runtime</scope>
    </dependency>
</dependencies>