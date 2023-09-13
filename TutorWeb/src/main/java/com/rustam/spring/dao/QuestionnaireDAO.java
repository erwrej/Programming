package com.rustam.spring.dao;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Component;

import com.rustam.spring.models.Questionnaire;

@Component
public class QuestionnaireDAO {
    private final JdbcTemplate jdbcTemplate;
    //private final GeneratedKeyHolder generatedKeyHolder;
    //private int lastId;

    @Autowired
    public QuestionnaireDAO(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public Questionnaire show(int id) {
        return jdbcTemplate.query("SELECT * FROM Questionnaires WHERE id=?", new Object[] { id },
                new BeanPropertyRowMapper<>(Questionnaire.class))
                .stream().findAny().orElse(null);
    }

    public void save(int id, Questionnaire questionnaire) {
        jdbcTemplate.update(
                "INSERT INTO Questionnaires VALUES(1,?,?,?,?,?,?,?,?,?,?,?,?)",
                questionnaire.getName(), questionnaire.getSurname(), questionnaire.getCity(),
                questionnaire.getSchoolSubjects(),questionnaire.getBio(),
                questionnaire.getWorkExperience(),questionnaire.isTeachingAtStudentsHome(),
                questionnaire.isTeachingAtTutorsHome(),questionnaire.isTeachingOnline(),
                questionnaire.getPricePerHour(),questionnaire.getAge(), questionnaire.getUserId()
                );
    }

    public void update(int id, Questionnaire questionnaire) {
        jdbcTemplate.update(
                "UPDATE Questionnaires SET name=?,surname=?,city=?,schoolSubjects=?,bio=?,workExperience=?,isTeachingAtStudentsHome=?,isTeachingAtTutorsHome=?,isTeachingOnline=?,pricePerHour=?,age=? WHERE id=?",
                questionnaire.getName(), questionnaire.getSurname(), questionnaire.getCity(),
                questionnaire.getSchoolSubjects(),questionnaire.getBio(),
                questionnaire.getWorkExperience(),questionnaire.isTeachingAtStudentsHome(),
                questionnaire.isTeachingAtTutorsHome(),questionnaire.isTeachingOnline(),
                questionnaire.getPricePerHour(),questionnaire.getAge(), id);
    }

    public void delete(int id) {
        jdbcTemplate.update(
            "DELETE FROM Questionnaires WHERE id=?", id
        );
    }
}
