package com.rustam.mobile_phone_payment.repositories;

import com.rustam.mobile_phone_payment.entities.BalancePhoneEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface BalancePhoneRepository extends JpaRepository<BalancePhoneEntity, Integer> {

    public Optional<BalancePhoneEntity> findByNumberPhone(Integer numberPhone);

    public List<BalancePhoneEntity> findAllByNameCustomer(String nameCustomer);
}
