/*
** EPITECH PROJECT, 2025
** Tek 2 B-OOP-400-LIL-4-1-arcade-martin.delebecque
** File description:
** IGameModule.hpp
*/

#ifndef IGAME_HPP
# define IGAME_HPP

namespace arc {
	class IGameModule {
		public:
			virtual void initGame() = 0;
			virtual void updateGame() = 0;
			virtual void displayGame() = 0;
			virtual void closeGame() = 0;
			virtual ~IGameModule() = default;
		protected:
		private:
	};
};

#endif