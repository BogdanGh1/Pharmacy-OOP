#pragma once

#include "Medicament.h"
#include "Repository.h"


class ActiuneUndo  //clasa abstracta
{
public:
	virtual void doUndo() = 0;  //metoda pur virtuala
	virtual ~ActiuneUndo() = default; //destructor virtual
};

class UndoAdauga : public ActiuneUndo
{
	Medicament med_adaugat;
	//RepoAct& rep;
	MedicamentRepository& rep;
public:
	//UndoAdauga(RepoAct& rep, const Activitate& act) : rep{rep}, act_adaugat{act}{}
	UndoAdauga(MedicamentRepository& rep, const Medicament& med) : rep{ rep }, med_adaugat{ med }{}
	void doUndo() override {
		rep.erase(med_adaugat.getDenumire(), med_adaugat.getProducator());
	}
	//virtual ~UndoAdauga() = default;
};

class UndoSterge : public ActiuneUndo
{
	Medicament med_sters;
	//RepoAct& rep;
	MedicamentRepository& rep;
public:
	//UndoSterge(RepoAct& rep, const Activitate& act) : rep{rep}, act_sters{act}{}
	UndoSterge(MedicamentRepository& rep, const Medicament& med) : rep{ rep }, med_sters{ med }{}
	void doUndo() override
	{
		rep.store(med_sters);
	}
	//virtual ~UndoSterge() = default;
};


class UndoModifica : public ActiuneUndo
{
	Medicament med_modif;
	//RepoAct& rep;
	MedicamentRepository& rep;
public:
	//UndoModifica(RepoAct& rep, const Activitate& act) : rep{rep}, act_modif{act}{}
	UndoModifica(MedicamentRepository& rep, const Medicament& med) : rep{ rep }, med_modif{ med }{}
	void doUndo() override
	{
		rep.modify(med_modif.getDenumire(), med_modif.getProducator(), med_modif.getSubstantaActiva(), med_modif.getPret());
	}
	//virtual ~UndoModifica() = default;
};