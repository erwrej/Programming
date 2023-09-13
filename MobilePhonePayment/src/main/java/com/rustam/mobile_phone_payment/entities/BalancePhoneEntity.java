package com.rustam.mobile_phone_payment.entities;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.experimental.Accessors;
import org.hibernate.annotations.GenericGenerator;

@Entity
@NoArgsConstructor
@AllArgsConstructor
@Data
@Table(name = "balance_phone")
@Accessors(chain = true)
public class BalancePhoneEntity {
    @Id
    @GenericGenerator(name = "generator", strategy = "increment")
    @GeneratedValue(generator = "generator")
    Integer id;

    @Column(name = "number_phone")
    Integer numberPhone;

    @Column(name = "name_customer")
    String nameCustomer;

    Integer balance;
}
