package com.rustam.spring.models;

import com.rustam.spring.Age;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.EnumType;
import jakarta.persistence.Enumerated;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Entity
@Table(name="Orders", catalog = "Spring", schema = "public")
public class Order {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Column(unique = true, nullable = false)
    private int id;

    private String header;

    @Column(nullable = false)
    private int studentId;

    @Column(nullable = false)
    private String subject;

    @Column(nullable = false)
    private int minPrice;

    @Column(nullable = false)
    private int maxPrice;

    private String city;

    @Column(nullable = false)
    private boolean isAtStudentsHome;

    @Column(nullable = false)
    private boolean isAtTutorsHome;

    @Column(nullable = false)
    private boolean isOnline;

    private String description;

    @Enumerated(EnumType.STRING)
    private Age age;

}
