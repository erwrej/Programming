package com.rustam.spring.dao;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Component;

import com.rustam.spring.models.Login;
import com.rustam.spring.models.User;

@Component
public class UserDAO {
    private final JdbcTemplate jdbcTemplate;
    // TODO make an exception
    private final Integer USER_NOT_FOUND = -1;

    @Autowired
    public UserDAO(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public Object findUserWithLoginAndPasswordAndReturnId(Login login) {
        User foundUser;
        if (isLogin(login)) {
            foundUser = jdbcTemplate.query("SELECT * FROM \"Users\" WHERE login=?",
                    new Object[] { login.getLogin() },
                    new BeanPropertyRowMapper<>(User.class))
                    .stream().findAny().orElse(null);
        } else {
            foundUser = jdbcTemplate.query("SELECT * FROM \"Users\" WHERE email=?",
                    new Object[] { login.getLogin() },
                    new BeanPropertyRowMapper<>(User.class))
                    .stream().findAny().orElse(null);
        }
        if (login.getPassword().equals(foundUser.getPassword())) {
            return foundUser.getId();
        } else {
            return USER_NOT_FOUND;
        }
    }

    public User showProfile(int id) {
        User user = jdbcTemplate.query("SELECT * FROM \"Users\" WHERE id=?", new Object[] { id },
                new BeanPropertyRowMapper<>(User.class))
                .stream().findAny().orElse(null);
        return user;
    }

    // TODO add tutor questinnaire creation
    public void save(User user) {
        jdbcTemplate.update(
                "INSERT INTO \"Users\"(login, password, email, status, phone) VALUES(?,?,?,?,?)",
                user.getLogin(), user.getPassword(), user.getEmail(),
                user.getStatus(), user.getPhone());
    }

    public void update(int id, User user) {
        jdbcTemplate.update(
                "UPDATE \"Users\" SET login=?, password=?, email=?, status=? WHERE id=?",
                user.getLogin(), user.getPassword(), user.getEmail(), user.getStatus(), id);
    }

    public void delete(int id) {
        jdbcTemplate.update(
                "DELETE FROM \"Users\" WHERE id=?", id);
    }

    public boolean isAlreadySaved(User user) {
        if (jdbcTemplate.query("SELECT * FROM \"Users\" WHERE login=? OR email=? OR phone=?",
                new Object[] { user.getLogin(), user.getEmail(), user.getPhone() },
                new BeanPropertyRowMapper<>(User.class))
                .stream().findAny().orElse(null) != null) {
            return true;
        } else {
            return false;
        }
    }

    private boolean isLogin(Login login) {
        String log = login.getLogin();
        for (int i = 0; i < log.length(); i++) {
            if (log.charAt(i) == '@') {
                return false;
            }
        }
        return true;
    }
}
