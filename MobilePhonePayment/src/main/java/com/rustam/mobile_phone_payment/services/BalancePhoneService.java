package com.rustam.mobile_phone_payment.services;

import com.rustam.mobile_phone_payment.dto.BalancePhoneDto;
import com.rustam.mobile_phone_payment.entities.BalancePhoneEntity;
import com.rustam.mobile_phone_payment.exceptions.ResourceNotFoundException;
import com.rustam.mobile_phone_payment.mappers.BalancePhoneMapper;
import com.rustam.mobile_phone_payment.repositories.BalancePhoneRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class BalancePhoneService {

    private final BalancePhoneRepository balancePhoneRepository;
    private final BalancePhoneMapper balancePhoneMapper;

    public List<BalancePhoneDto> findAll() {
        return balancePhoneRepository.findAll().stream()
                .map(balancePhoneMapper::mapToBalancePhoneDto)
                .collect(Collectors.toList());
    }

    public BalancePhoneDto findById(Integer id) {
        return balancePhoneMapper.mapToBalancePhoneDto(
                balancePhoneRepository.findById(id)
                        .orElseThrow(() -> {
                            return new ResourceNotFoundException(
                                    "Phone with id " + id + " not found");
                        }));
    }

    public BalancePhoneDto findByNumberPhone(Integer phone) {
        return balancePhoneMapper.mapToBalancePhoneDto(
                balancePhoneRepository.findByNumberPhone(phone)
                        .orElse(new BalancePhoneEntity()));
    }

    public List<BalancePhoneDto> findByNameCustomer(String nameCustomer) {
        return balancePhoneRepository.findAllByNameCustomer(nameCustomer).stream()
                .map(balancePhoneMapper::mapToBalancePhoneDto)
                .collect(Collectors.toList());
    }

    public void save(BalancePhoneDto balancePhoneDto) {
        balancePhoneRepository.save(balancePhoneMapper
                .mapToBalancePhoneEntity(balancePhoneDto));
    }

    public void deleteById(Integer id) {
        balancePhoneRepository.deleteById(id);
    }

    public void saveAll(List<BalancePhoneDto> dto) {
        balancePhoneRepository.saveAll(
                dto.stream().map(balancePhoneMapper::mapToBalancePhoneEntity)
                        .collect(Collectors.toList()));

    }

    public void addingMoneyToBalance(Integer phoneNumber, Integer sum) {
        BalancePhoneDto byPhoneNumber = findByNumberPhone(phoneNumber);
        byPhoneNumber.setBalance(byPhoneNumber.getBalance() + sum);
        save(byPhoneNumber);
    }
}
