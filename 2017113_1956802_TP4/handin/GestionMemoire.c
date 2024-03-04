#include "./libs/lib.h"
unsigned int calculerNumeroDePage(unsigned long adresse) {
	// TODO
    return adresse >> 10;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse) {
	//limite en 1024 bits
    return adresse & 0x3FF;
	
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage) {
	// TODO
    numeroDePage = numeroDePage <<10;
	unsigned long adresseComplete = deplacementDansLaPage + numeroDePage;
	return adresseComplete;
}

void rechercherTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {

	for(int i =0; i< TAILLE_TLB; ++i)
	{
        if (mem->tlb->entreeValide[i] && mem->tlb->numeroPage[i]== calculerNumeroDePage(req->adresseVirtuelle) )
		{
            long TLBCadre= mem->tlb->numeroCadre[i];
            unsigned long adresse= calculerAdresseComplete(TLBCadre, calculerDeplacementDansLaPage(req->adresseVirtuelle));
			mem->tlb->dernierAcces[i]=req-> date;
			req->adressePhysique=adresse;
			return;
        }
    }
	req->adressePhysique=0;
	return;
}

void rechercherTableDesPages(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	unsigned long adresseVirtuelle = req ->adresseVirtuelle;
	unsigned long numeroPage = calculerNumeroDePage(adresseVirtuelle);

	if(mem->tp->entreeValide[numeroPage])
	{
		unsigned long numeroCardre = mem ->tp->numeroCadre[numeroPage];
		unsigned long deplacementDansPage = calculerDeplacementDansLaPage(adresseVirtuelle);
		req -> adressePhysique = calculerAdresseComplete(numeroCardre, deplacementDansPage);
		return;
	}

	req->adressePhysique = 0;
	return;
}

void ajouterDansMemoire(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	//TODO
	unsigned long adresseVirtuelle = req->adresseVirtuelle;
	unsigned long numeroPage = calculerNumeroDePage(adresseVirtuelle);
	for(int i = 0; i<TAILLE_MEMOIRE;++i)
	{
		if(!mem->memoire->utilisee[i])
		{

			unsigned long numeroCardre = i;
			unsigned long deplacementDansPage = calculerDeplacementDansLaPage(adresseVirtuelle);
			unsigned long adressePhysique = calculerAdresseComplete(numeroCardre, deplacementDansPage);
			mem->memoire->numeroPage[i] = numeroPage;
			mem->memoire->utilisee[i]=1;
			mem->memoire->dernierAcces[i] = req->date;
			mem->memoire->dateCreation[i] = mem->memoire->dernierAcces[i];
			req->adressePhysique = adressePhysique;
			return;
		}
	}
	return;
}

void mettreAJourTLB(struct RequeteMemoire* req, struct SystemeMemoire* mem) {
	// TODO
	unsigned long numeroPage = calculerNumeroDePage(req ->adresseVirtuelle);
	unsigned long numeroCadre = mem->tp->numeroCadre[numeroPage];
	unsigned long deplacement = calculerDeplacementDansLaPage(req ->adresseVirtuelle);
	unsigned long adressePhysique = calculerAdresseComplete(numeroCadre,deplacement);
	
	int index;
	unsigned long dateDeDebut = mem->tlb->dateCreation[0];
	
	for(int i = 0; i<TAILLE_TLB; ++i)
	{
		if(mem->tlb->entreeValide[i] == 0)
		{
			mem->tlb->numeroCadre[i] = numeroCadre;
			mem->tlb->numeroPage[i] = numeroPage;
			mem -> tlb->dateCreation[i] = req->date;
			mem->tlb->dernierAcces[i]=mem -> tlb->dateCreation[i];
			mem->tlb->entreeValide[i]= 1;

			req->adressePhysique = adressePhysique;
			return;
		}
		else if(mem->tlb->dateCreation[i] < dateDeDebut && mem ->tlb->entreeValide[i])
		{	

			dateDeDebut = mem->tlb->dateCreation[i];
			index = i;
		}
		
	}

	mem->tlb->numeroCadre[index] = numeroCadre;
	mem->tlb->numeroPage[index] = numeroPage;
	mem->tlb->dateCreation[index] = req ->date;
	mem->tlb->dernierAcces[index] = req ->date;
	mem->tlb->entreeValide[index] = 1;

	req->adressePhysique=adressePhysique;
	return;
}

// NE PAS MODIFIER
int main() {
    evaluate(
		&calculerNumeroDePage, 
		&calculerDeplacementDansLaPage, 
		&calculerAdresseComplete, 
        &rechercherTLB, 
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire
    );
    return 0;
}
