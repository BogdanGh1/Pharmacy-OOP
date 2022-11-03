#pragma once
#include "Medicament.h"
#include <assert.h>
string Medicament::getDenumire() const {
	return this->denumire;
}
string Medicament::getProducator() const {
	return this->producator;
}
string Medicament::getSubstantaActiva() const {
	return this->substantaActiva;
}
double Medicament::getPret() const {
	return this->pret;
}

void Medicament::setProducator(string producatorNou) {
	this->producator = producatorNou;
}
void Medicament::setDenumire(string denumireNoua) {
	this->denumire = denumireNoua;
}
void Medicament::setSubstantaActiva(string substantaActivaNoua) {
	this->substantaActiva = substantaActivaNoua;
}
void Medicament::setPret(double pretNou) {
	this->pret = pretNou;
}

void testGetSet() {
	Medicament med{ "Nurofen", "Reckitt Benckiser(Romania) SRL","Ibuprofen",15 };
	assert(med.getDenumire() == "Nurofen");
	assert(med.getProducator() == "Reckitt Benckiser(Romania) SRL");
	assert(med.getSubstantaActiva() == "Ibuprofen");
	assert(med.getPret() == 15);

	med.setDenumire("NO-SPA");
	med.setProducator("Sanofi Romania SRL");
	med.setSubstantaActiva("clorhidrat de drotaverina");
	med.setPret(20);

	assert(med.getDenumire() == "NO-SPA");
	assert(med.getProducator() == "Sanofi Romania SRL");
	assert(med.getSubstantaActiva() == "clorhidrat de drotaverina");
	assert(med.getPret() == 20);



}

void testeDomain() {
	testGetSet();
}