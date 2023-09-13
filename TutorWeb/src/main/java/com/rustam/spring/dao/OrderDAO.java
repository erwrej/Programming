package com.rustam.spring.dao;

import com.rustam.spring.models.Order;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class OrderDAO {
    private final JdbcTemplate jdbcTemplate;

    @Autowired
    public OrderDAO(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public List<Order> getOrdersByUserId(int userId) {
        return jdbcTemplate.query("SELECT * FROM \"Orders\" WHERE studentId=?",
                new Object[]{userId}, new BeanPropertyRowMapper<>(Order.class));
    }

    public Order getById(int id) {
        return jdbcTemplate.query("SELECT * FROM \"Orders\" WHERE id=?", new Object[]{id},
                        new BeanPropertyRowMapper<>(Order.class))
                .stream().findAny().orElse(null);
    }

    public void save(Order order) {
        jdbcTemplate.update(
                "INSERT INTO \"Orders\" (header,subject,minPrice,maxPrice,city"
                        + ",isAtStudentsHome,isAtTutorsHome,isOnline,description, age)"
                        + "VALUES(1,?,?,?,?,?,?,?,?,?,?)",
                order.getHeader(), order.getSubject(),
                order.getMinPrice(), order.getMaxPrice(), order.getCity(),
                order.isAtStudentsHome(), order.isAtTutorsHome(), order.isOnline(),
                order.getDescription(), order.getAge().getDisplayValue());
    }

    public void updateById(int id, Order order) {
        jdbcTemplate.update(
                "UPDATE \"Orders\" SET header=?,subject=?,minPrice=?,maxPrice=?,city=?,isAtStudentsHome=?,isAtTutorsHome=?,isOnline=?,description=?,age=? WHERE id=?",
                order.getHeader(), order.getSubject(),
                order.getMinPrice(), order.getMaxPrice(), order.getCity(),
                order.isAtStudentsHome(), order.isAtTutorsHome(), order.isOnline(),
                order.getDescription(), order.getAge().getDisplayValue(), id);
    }

    public void deleteById(int id) {
        jdbcTemplate.update(
                "DELETE FROM \"Orders\" WHERE id=?", id);
    }

}
