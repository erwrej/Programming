package com.rustam.spring.models;

import java.util.Set;

import com.rustam.spring.Age;

public class Questionnaire {
    private int id;

    private int userId;

    private String name;

    private String surname;

    private String city;

    private Set<String> schoolSubjects;

    private String bio;

    private int workExperience;

    private boolean isTeachingAtStudentsHome;

    private boolean isTeachingAtTutorsHome;

    private boolean isTeachingOnline;

    private int pricePerHour;

    private Age age;

    public Questionnaire(int id, int userId, String name, String surname, String city, Set<String> schoolSubjects,
            String bio, int workExperience, boolean isTeachingAtStudentsHome, boolean isTeachingAtTutorsHome,
            boolean isTeachingOnline, int pricePerHour, Age age) {
        this.id = id;
        this.userId = userId;
        this.name = name;
        this.surname = surname;
        this.city = city;
        this.schoolSubjects = schoolSubjects;
        this.bio = bio;
        this.workExperience = workExperience;
        this.isTeachingAtStudentsHome = isTeachingAtStudentsHome;
        this.isTeachingAtTutorsHome = isTeachingAtTutorsHome;
        this.isTeachingOnline = isTeachingOnline;
        this.pricePerHour = pricePerHour;
        this.age = age;
    }

    public Age getAge() {
        return age;
    }

    public void setAge(Age age) {
        this.age = age;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public Set<String> getSchoolSubjects() {
        return schoolSubjects;
    }

    public void setSchoolSubjects(Set<String> schoolSubjects) {
        this.schoolSubjects = schoolSubjects;
    }

    public String getBio() {
        return bio;
    }

    public void setBio(String bio) {
        this.bio = bio;
    }

    public int getWorkExperience() {
        return workExperience;
    }

    public void setWorkExperience(int workExperience) {
        this.workExperience = workExperience;
    }

    public boolean isTeachingAtStudentsHome() {
        return isTeachingAtStudentsHome;
    }

    public void setTeachingAtStudentsHome(boolean isTeachingAtStudentsHome) {
        this.isTeachingAtStudentsHome = isTeachingAtStudentsHome;
    }

    public boolean isTeachingAtTutorsHome() {
        return isTeachingAtTutorsHome;
    }

    public void setTeachingAtTutorsHome(boolean isTeachingAtTutorsHome) {
        this.isTeachingAtTutorsHome = isTeachingAtTutorsHome;
    }

    public boolean isTeachingOnline() {
        return isTeachingOnline;
    }

    public void setTeachingOnline(boolean isTeachingOnline) {
        this.isTeachingOnline = isTeachingOnline;
    }

    public int getPricePerHour() {
        return pricePerHour;
    }

    public void setPricePerHour(int pricePerHour) {
        this.pricePerHour = pricePerHour;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

}
